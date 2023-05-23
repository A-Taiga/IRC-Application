#include "topBar.hpp"
#include "FL/Enumerations.H"

GUI::TopBar::TopBar(int x, int y, int w, int h)
:Fl_Menu_Bar(x,y,w,h)
{
	add("File",0,0);
	add("Settings",0,0);
	add("Help",0,0);
	add("About",0,0);

	box(FL_NO_BOX);

}