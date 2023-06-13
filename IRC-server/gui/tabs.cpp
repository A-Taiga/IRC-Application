#include "tabs.hpp"
#include "FL/Enumerations.H"
#include "bottomBar.hpp"
#include "serverTab.hpp"
#include "mainWindow.hpp"

GUI::Tabs::Tabs(int x, int y, int w, int h, BottomBar* bottomBar, State& s)
:Fl_Tabs(x,y,w,h)
,bBar(bottomBar)
, state(s)
{

	serverTab = new ServerTab(x,y+20,w,h-40,"server",bBar, s);
	box(FL_FRAME_BOX);
	end();
}
