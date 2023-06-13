#include "state.hpp"
#include "FL/Fl_Text_Buffer.H"

void runHandler(State* st, Fl_Text_Buffer* buffer) { st->server->run(st->running, buffer); }

State::State()
    : running(false)
{
}
void State::createServer(const char* port, Fl_Text_Buffer* buffer)
{
	server = new IRC::Server(port);
	server->listen(20);
	running = true;
	thread  = std::thread(runHandler, this, buffer);
}

void State::endServer()
{
	running = false;
	/*
	this causes program to seem like it's not
	responding because fltk has to wait for the thread to join
	this might be beecause of the the time set for kevent
	to check for new events
	*/
	thread.join();
	delete server;
	server = nullptr;
}

State::~State()
{
	if (server != nullptr)
		server->~Server();
}
