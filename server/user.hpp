#ifndef USER_HPP
#define USER_HPP

#include <sys/types.h>
#include <arpa/inet.h>
#include <string>

namespace IRC
{
	class User
	{
		private:
		int fd;
		std::string address;
		std::string username;
		public:
		User(int fd, std::string address, std::string username);
		User(){};
		void print_msg(char& buffer);
		~User();

	};
}


#endif