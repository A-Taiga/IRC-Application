#include "bottomBar.hpp"
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <ctime>

GUI::BottomBar::BottomBar(int x, int y, int w, int h)
    : Fl_Group(x, y, w, h)
{
	/* clock */
	clock = new Fl_Box(w - 100, y, 100, h, getTime());
	clock->box(FL_NO_BOX);
	clock->align(FL_ALIGN_INSIDE | FL_ALIGN_CENTER);
	Fl::add_timeout(1, clock_timeout, this);

	/*server status*/
	serverStatus = new Fl_Box(x, y, 100, h, "offline");
	serverStatus->box(FL_FLAT_BOX);

	/*this*/
	box(FL_FLAT_BOX);
	end();
}

char* GUI::BottomBar::getTime()
{
	static char buffer[20];
	time_t      t  = 0;
	tm*         tt = nullptr;
	time(&t);
	tt = localtime(&t);
	strftime(buffer, sizeof(buffer), "%r", tt);
	return buffer;
}

void GUI::BottomBar::clock_timeout(void* v)
{
	((BottomBar*)v)->clock->label(((BottomBar*)v)->getTime());
	Fl::repeat_timeout(1, clock_timeout, v);
}

