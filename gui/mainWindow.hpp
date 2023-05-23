#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP
#include "bottomBar.hpp"
#include "state.hpp"
#include "tabs.hpp"
#include "topBar.hpp"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
namespace GUI
{
	class MainWindow : public Fl_Window
	{
		public:
		State      state;
		bool       running = false;
		TopBar*    topBar  = nullptr;
		Tabs*      tabs    = nullptr;
		BottomBar* bBar    = nullptr;

		MainWindow(int w, int h, const char* label = 0);
	};
} // namespace GUI

#endif