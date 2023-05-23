#ifndef TABS_HPP
#define TABS_HPP
#include "FL/Fl_Tabs.H"
#include "bottomBar.hpp"
#include "serverTab.hpp"
#include "state.hpp"
namespace GUI
{

	class Tabs : public Fl_Tabs
	{
		public:
		State& state;
		BottomBar*   bBar      = nullptr;
		ServerTab*   serverTab = nullptr;
		bool         running   = false;
		Tabs(int x, int y, int w, int h, BottomBar* bottomBar, State& s);
	};
} // namespace GUI

#endif