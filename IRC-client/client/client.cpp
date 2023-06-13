#include "client.hpp"
#include <netdb.h>
#include <sys/socket.h>
#include <iostream>
#include "utility.hpp"


IRC::Client::Client(const char* _ip, const char* _port)
: ip(_ip)
, port(_port)
, socket_fd(0)
{
	setup();
}
void IRC::Client::setup()
{
	return; ///REMOVE WHEN NOT TESTING UI
 	int status = 0;
	struct addrinfo hints = {};
	addrinfo* temp_info   = nullptr;
	addrinfo* server_info = nullptr;
	int temp_fd = 0;

	hints.ai_family   = AF_UNSPEC;   /*IPv4 or IPv6*/
	hints.ai_socktype = SOCK_STREAM; /*socket type*/
	hints.ai_flags    = AI_PASSIVE;  /*choose ip for the server*/
	hints.ai_protocol = 0;           /*any protocol*/

	status = getaddrinfo(ip.c_str(),port.c_str(),&hints,&temp_info);
	if(status != 0)
		std::cerr << "Server::Srever getaddrinfo(): " << gai_strerror(status) << std::endl;
	
	for(server_info = temp_info; server_info != nullptr; server_info = server_info->ai_next)
	{
		socket_fd = socket(server_info->ai_family,server_info->ai_socktype,server_info->ai_protocol);
		if(socket_fd == -1)
			continue;
		if(connect(socket_fd,server_info->ai_addr,server_info->ai_addrlen) != -1)
			break;
		close(socket_fd);
	}
	freeaddrinfo(temp_info);
	if(server_info == nullptr)
		ERROR(__FILE__, __LINE__, __PRETTY_FUNCTION__, "failed to bind");
}

void IRC::Client::run()
{
	char buffer[1024];
	while(true)
	{
		::recv(socket_fd, buffer, 1024, 0);

	}
}
