#ifndef SERVER_HPP
#define SERVER_HPP
#include "user.hpp"
#include <iostream>
#include <netdb.h>
#include <sys/event.h>
#include <sys/time.h>
#include <unordered_map>
#include <vector>
#include <FL/Fl_Text_Buffer.H>
namespace IRC
{

	class Server
	{
		private:
		std::string port;
		int                           listen_socket;
		int                           kq;
		int                           event_num;
		timespec                      timeout;
		struct kevent                 change_list;
		std::vector<struct kevent>    event_list;
		std::unordered_map<int, int>  change_map;
		std::unordered_map<int, User> users;

		void        accept(std::string welcome_msg);
		void*       get_in_addr(sockaddr* sa);
		void        remove_event(int index, int fd);
		void        event_handler(Fl_Text_Buffer* textBuffer);
		std::string get_user_address(sockaddr_storage& client);
		
		public:
		explicit Server(const char* port);
		void setup();
		void listen(int queue_size);
		void run(bool& running, Fl_Text_Buffer* textBuffer);
		~Server();
	};
} // namespace IRC

#endif