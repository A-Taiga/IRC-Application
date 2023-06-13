#include "tabs.hpp"
#include "FL/Fl_Group.H"
#include "FL/Fl_Input.H"
#include "FL/Fl_Tabs.H"
#include "FL/Fl.H"
GUI::Tabs::Tabs(int x, int y, int w, int h, const char* label)
    : Fl_Tabs(x, y, w, h, label)
    , settings(new SettingsTab(x, y + 20, w, h - 20, "Settings"))
    , chat(new ChatTab(x, y + 20, w, h - 20, "Chat"))
{
	end();
}

////////////////////////////////////////////////////////////////////// CHAT TAB
GUI::ChatTab::ChatTab(int x, int y, int w, int h, const char* label)
    : Fl_Group(x, y, w, h, label)
{
	end();
}

GUI::SettingsTab::SettingsTab(int x, int y, int w, int h, const char* label)
    : Fl_Group(x, y, w, h, label)
	, ipInput(new Fl_Input(x+100,y+20,100,20))
	, portInput(new Fl_Input(ipInput->x(),ipInput->y()+ipInput->h()+5,100,20))
	, connect(new Fl_Button(ipInput->x(),portInput->y()+portInput->h()+5,100,20,"Enter"))
{
	ipInput->label("IP Address");
	portInput->label("Port");

	end();
}
