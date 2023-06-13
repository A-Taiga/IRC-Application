
#include "mainWindow.hpp"
#include <FL/Fl.H>
#include <iostream>
#include "../client/client.hpp"
#include <thread>
#include "../client/msgHandler.hpp"

// void handler(IRC::Client& client)
// {

// }

int main()
{
	IRC::Client client("::1","3000");

	
	IRC::State state(client);

	GUI::MainWindow window(600,400, state);
	window.show();

	// std::thread t = std::thread(handler, std::ref(client));

	// IRC::Client cl("::1","3000");
	
	return Fl::run();
}