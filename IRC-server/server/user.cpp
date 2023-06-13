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
	username.erase(std::remove(username.begin(),username.end(),'\n'),username.end());
    std::cout << username << std::endl;

}
void IRC::User::print_msg(char& buffer)
{
    std::string msg = MAGENTA;
    msg += "<";
    msg += RESET;
    msg += username;
    msg += MAGENTA;
    msg += "> ";
    msg += RESET;
    msg += &buffer;
    
    msg.erase(std::remove(msg.begin(),msg.end(),'\n'),msg.end());
    std::string n = "<";
    n += username;
    n += ">";
    std::cout << n << std::endl;
    ::send(fd,msg.data(),msg.size(),0);

}
IRC::User::~User()
{
	close(fd);

	std::cout << "<" << username << "> ip: " << address << " disconnected" << std::endl;
}
