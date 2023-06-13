#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP
#include "FL/Fl.H"
#include <FL/Fl_Window.H>
#include "tempArea.hpp"
#include "../client/msgHandler.hpp"
#include "tabs.hpp"


namespace GUI
{
	class MainWindow: public Fl_Window
	{
		public:
		Tabs tabs;
		// Group* area;
		IRC::State& state;
		MainWindow(int w, int h, IRC::State& s);
	};
}



#endif