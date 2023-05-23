#include <FL/Fl.H>
#include "mainWindow.hpp"
int main()
{
	GUI::MainWindow window(700,500,"Server");
	window.end();
	window.show();
	return Fl::run();
}