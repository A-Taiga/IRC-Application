#ifndef TOPBAR_HPP
#define TOPBAR_HPP
#include <FL/Fl_Menu_Bar.H>

namespace GUI
{
	class TopBar: public Fl_Menu_Bar
	{
		public:
		TopBar(int x, int y, int w, int h);
	};
}
#endif