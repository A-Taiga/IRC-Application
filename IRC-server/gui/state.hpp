#ifndef STATE_HPP
#define STATE_HPP
#include "../server/server.hpp"
#include <FL/Fl_Text_Buffer.H>
#include <thread>


class State;
void runHandler(State* st,Fl_Text_Buffer* buffer);

class State
{
	public:
	IRC::Server* server = nullptr;
	std::thread  thread;
	bool         running;
	State();
	void createServer(const char* port, Fl_Text_Buffer* buffer);
	void endServer();
	~State();
};

#endif