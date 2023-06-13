#include "server.hpp"
#include "FL/Fl_Text_Buffer.H"
#include "utility.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <algorithm>

IRC::Server::Server(const char* p)
    : listen_socket{0}
    , port(p)
    , kq{kqueue()}
    , event_num{0}
    , timeout{5, 0}
    , change_list{}
    , event_list{}
{
	setup();
}
void IRC::Server::setup()
{
	if (kq == -1)
		ERROR(__FILE__, __LINE__, __PRETTY_FUNCTION__, "kq");
	const int option      = 1;
	int       status      = 0;
	addrinfo* temp_info   = {nullptr};
	addrinfo* server_info = {nullptr};
	addrinfo  hints       = {};

	hints.ai_family   = AF_UNSPEC;   /*IPv4 or IPv6*/
	hints.ai_socktype = SOCK_STREAM; /*socket type*/
	hints.ai_flags    = AI_PASSIVE;  /*choose ip for the server*/
	hints.ai_protocol = 0;           /*any protocol*/

	status = getaddrinfo(nullptr, port.c_str(), &hints, &temp_info);
	if (status != 0)
		std::cerr << "Server::Srever getaddrinfo(): " << gai_strerror(status) << std::endl;

	/*begin looping through available addresses*/
	for (server_info = temp_info; server_info != nullptr; server_info = server_info->ai_next)
	{

		listen_socket =
		    socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);
		if (listen_socket == -1)
			ERROR(__FILE__, __LINE__, __PRETTY_FUNCTION__, "socket()");

		if (setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) == -1)
			ERROR(__FILE__, __LINE__, __PRETTY_FUNCTION__, "setsockopt()");

		if (bind(listen_socket, server_info->ai_addr, server_info->ai_addrlen) == -1)
		{
			close(listen_socket);
			std::cerr << "server bind: " << std::strerror(errno) << std::endl;
			continue;
		}
		break; /*found one*/
	}
	freeaddrinfo(temp_info);
	if (server_info == nullptr)
		ERROR(__FILE__, __LINE__, __PRETTY_FUNCTION__, "failed to bind");

	event_list.emplace_back();
	EV_SET(&change_list, listen_socket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, 0);
}
void IRC::Server::listen(int queue_size)
{
	std::cout << GREEN "server started" RESET << std::endl;
	if (::listen(listen_socket, queue_size) == -1)
		ERROR(__FILE__, __LINE__, __PRETTY_FUNCTION__, "listen()");
}

void IRC::Server::accept(std::string welcome_msg)
{
	std::string      user_address = {};
	// std::string      uname(10, '\0');
	sockaddr_storage connection = {};
	socklen_t        sin_size   = 0;
	int              client_fd  = 0;

	sin_size  = sizeof(connection);
	client_fd = ::accept(listen_socket, reinterpret_cast<sockaddr*>(&connection), &sin_size);
	if (client_fd == -1)
		ERROR(__FILE__, __LINE__, __PRETTY_FUNCTION__, "accept()");

	user_address = get_user_address(connection);
	// char buff[255];
	// ::recv(client_fd,buff, 255, 0);
	// std::string uname(buff);

	// std::cout << "new client connection: " << user_address << " " << uname << std::endl;

	users.try_emplace(client_fd, client_fd, user_address, "uname.data()"); // switch to just emplace 

	// event_list.emplace_back();
	EV_SET(&change_list, client_fd, EVFILT_READ, EV_ADD, 0, 0, 0);

	kevent(kq, &change_list, 1, nullptr, 0, &timeout);

	if (::send(client_fd, welcome_msg.data(), welcome_msg.size(), 0) == -1)
		ERROR(__FILE__, __LINE__, __PRETTY_FUNCTION__, "send()");
}

void* IRC::Server::get_in_addr(sockaddr* sa)
{
	// if family is ipv4 return its address
	if (sa->sa_family == AF_INET)
		return &(reinterpret_cast<sockaddr_in*>(sa)->sin_addr);
	// else return ipv6
	return &(reinterpret_cast<sockaddr_in6*>(sa)->sin6_addr);
}

void IRC::Server::remove_event(int index, int fd)
{
	/* remove event from event_list  */
	std::swap(event_list[index], event_list.back());
	event_list.pop_back();

	/* delete the event in change_list */
	EV_SET(&change_list, fd, EVFILT_READ, EV_DELETE, 0, 0, 0);
	users.erase(fd);
}

void IRC::Server::event_handler(Fl_Text_Buffer* textBuffer)
{
	int event_fd = 0;
	for (int i = 0; i < event_num; i++)
	{
		event_fd = event_list[i].ident;

		/* not sure what to put here yet */
		if (event_list[i].flags & EV_ERROR)
		{
			std::cout << "some error" << std::endl;
		}
		/* client has disconnected */
		if (event_list[i].flags & EV_EOF)
		{
			remove_event(i, event_fd);
		}
		/* if new client is requesting connection */
		else if (event_fd == listen_socket)
		{
			accept("Welcome\n");
		}
		/* if client is sending data (only for testing for now)*/
		else if (event_list[i].flags & EV_ADD)
		{
			char buffer[1024] = {};
			if (recv(event_fd, buffer, sizeof(buffer), 0) == -1)
				ERROR(__FILE__, __LINE__, __PRETTY_FUNCTION__, "recv()");

			users[event_list[i].ident].print_msg(*buffer);

			textBuffer->append(buffer);
			textBuffer->append(" \n");


			for (const auto& [key, value] : users)
			{
				if (key != event_fd)
				{
					users[key].print_msg(*buffer);
					// ::send(key,buffer,sizeof(buffer),0);
				}
			}
		}
	}
}

void IRC::Server::run(bool& running, Fl_Text_Buffer* textBuffer)
{
	event_num = kevent(kq, &change_list, 1, nullptr, 0, &timeout);

	if (event_num == -1)
		ERROR(__FILE__, __LINE__, __PRETTY_FUNCTION__, "kevent()");
	while (running)
	{
		event_num = kevent(kq, nullptr, 0, event_list.data(), 1, &timeout);
		if (event_num == -1)
			ERROR(__FILE__, __LINE__, __PRETTY_FUNCTION__, "while() kevent()");
		event_handler(textBuffer);
	}
}

std::string IRC::Server::get_user_address(sockaddr_storage& client)
{
	std::string address(INET6_ADDRSTRLEN, '\0');
	inet_ntop(
	    client.ss_family,
	    get_in_addr(reinterpret_cast<sockaddr*>(&client)),
	    address.data(),
	    sizeof(address)
	);
	return address;
}

IRC::Server::~Server() /* need to close client fds as well probably */
{
	close(listen_socket);
	close(kq);
	std::cout << RED "server ended" RESET << std::endl;
}