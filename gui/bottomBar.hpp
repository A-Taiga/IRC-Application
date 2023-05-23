#ifndef BOTTOMBAR_HPP
#define BOTTOMBAR_HPP
#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>
namespace GUI
{
	class BottomBar : public Fl_Group
	{
		public:
		Fl_Box* clock = nullptr;
		Fl_Box* serverStatus = nullptr;
		BottomBar(int x, int y, int w, int h);
		char*       getTime();
		static void clock_timeout(void* v);
	};

} // namespace GUI
#endif