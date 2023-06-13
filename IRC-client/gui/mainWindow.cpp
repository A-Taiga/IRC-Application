#include "mainWindow.hpp"
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include "tempArea.hpp"

GUI::MainWindow::MainWindow(int w, int h, IRC::State& s)
: Fl_Window(w,h)
, state(s)
{
	area = new Group(20,20,w-40,h-80, s);
	size_range(w,h);
	resizable(this);

	
	end();
}