#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string>

namespace IRC
{
	class Client
	{
		public:
		std::string ip;
		std::string port;
		int socket_fd;
		Client(const char* _ip, const char* _port);
		void setup();
		void run();
	};
}

#endif