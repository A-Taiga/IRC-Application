#include "user.hpp"
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include "utility.hpp"



IRC::User::User(int _fd, std::string _address, std::string _username)
    : fd(_fd)
    , address(_address)
    , username(_username)
{

}
void IRC::User::print_msg(char& buffer)
{
    std::string msg = MAGENTA;
    msg += "<";
    msg += RESET;
    msg += "USERNAME";
    msg += MAGENTA;
    msg += "> ";
    msg += RESET;
    msg += &buffer;
    std::cout << MAGENTA "<" RESET << username << MAGENTA "> " RESET << &buffer;
    ::send(fd,msg.data(),msg.size(),0);

}
IRC::User::~User()
{
	close(fd);

	std::cout << "<" << username << "> ip: " << address << " disconnected" << std::endl;
}
