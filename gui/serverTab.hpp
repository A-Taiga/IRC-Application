#ifndef SERVERTAB_HPP
#define SERVERTAB_HPP
#include "state.hpp"
#include "FL/Fl_Input.H"
#include "FL/Fl_Scrollbar.H"
#include "bottomBar.hpp"
#include <FL/Fl_Browser.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Widget.H>
#include <string>
#include <thread>
namespace GUI
{
	class ServerTab;
	class ChatWindow;
	class UserList;
	class Input;
	class InputScroll;
	class ServerTab : public Fl_Group
	{
		public:
		State& state;
		BottomBar*   bBar     = nullptr;
		Fl_Button*   start    = nullptr;
		Fl_Button*   stop     = nullptr;
		ChatWindow*  chat     = nullptr;
		UserList*    userList = nullptr;
		Fl_Input*    input    = nullptr; /*temp for now*/
		ServerTab(int x, int y, int w, int h, const char* label, BottomBar* bottomBar, State& s);
		static void start_cb(Fl_Widget* wg, void* v);
		static void stop_cb(Fl_Widget* wg, void* v);
		static void input_cb(Fl_Widget* wg, void* v);
	};

	class ChatWindow : public Fl_Text_Display
	{
		public:
		Fl_Text_Buffer* tBuffer = nullptr;
		Fl_Text_Buffer* sBuffer = nullptr;
		ChatWindow(int x, int y, int w, int h, const char* label = 0);
	};
	class UserList : public Fl_Browser
	{
		public:
		UserList(int x, int y, int w, int h);
	};

} // namespace GUI
#endif