#ifndef TEMPAREA_HPP
#define TEMPAREA_HPP
#include "FL/Fl_Text_Display.H"
#include "FL/Fl_Widget.H"
#include <FL/Fl.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include "../client/msgHandler.hpp"


namespace GUI
{
	class Group: Fl_Group
	{
		public:
		IRC::State& state;
		Fl_Text_Buffer* buffer;
		Fl_Text_Display* display;
		Fl_Input* input;
		Group(int x, int y, int w, int h, IRC::State& s);
		static void input_cb(Fl_Widget* wg, void* v);

	};
}

#endif