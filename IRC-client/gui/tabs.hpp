#ifndef TABS_HPP
#define TABS_HPP
#include "FL/Fl_Group.H"
#include <FL/Fl_Input.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Button.H>
namespace GUI
{

	class ChatTab;
	class SettingsTab;

	class Tabs : protected Fl_Tabs
	{
		public:
		SettingsTab* settings;
		ChatTab*     chat;
		Tabs(int x, int y, int w, int h, const char* label = 0);
	};

	class ChatTab : protected Fl_Group
	{
		public:
		ChatTab(int x, int y, int w, int h, const char* label);
	};

	class SettingsTab : protected Fl_Group
	{
		public:
		Fl_Input* ipInput;
		Fl_Input* portInput;
		Fl_Button* connect;
		SettingsTab(int x, int y, int w, int h, const char* label);
	};

} // namespace GUI

#endif