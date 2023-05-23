#include "serverTab.hpp"
#include "FL/Enumerations.H"
#include "FL/Fl_Browser_.H"
#include "FL/Fl_Button.H"
#include "FL/Fl_Input.H"
#include "FL/Fl_Multiline_Input.H"
#include "FL/Fl_Scrollbar.H"
#include "FL/Fl_Slider.H"
#include "FL/Fl_Text_Buffer.H"
#include "FL/Fl_Text_Display.H"
#include "FL/Fl_Widget.H"
#include "bottomBar.hpp"
#include <cstddef>


GUI::ServerTab::ServerTab(
    int x, int y, int w, int h, const char* label, BottomBar* bottomBar, State& s
)
    : Fl_Group(x, y, w, h, label)
    , bBar(bottomBar)
    , state(s)
{
	/*start server*/
	start = new Fl_Button(x + 10, y + 20, 80, 20, "start");
	start->callback(start_cb, this);

	/*stop server*/
	stop = new Fl_Button(x + 10, y + start->h() * 2 + 5, 80, 20, "stop");
	stop->callback(stop_cb, this);

	chat = new ChatWindow(start->w() + 20, start->y(), 450, h - start->y());

	userList = new UserList(
	    chat->x() + chat->w() + 5,
	    chat->y(),
	    w - chat->w() - start->w() - 35,
	    chat->h()
	);

	// input = new Input(chat->x(), chat->h() + chat->y() + 5, chat->w(), 20);
	input = new Fl_Input(chat->x(), chat->h() + chat->y() + 5, chat->w(), 20);
	input->callback(input_cb, chat);
	input->when(FL_WHEN_ENTER_KEY);
	end();
	/* start a thread to run the server */
	// thread = std::thread(&run, this);
}

void GUI::ServerTab::start_cb(Fl_Widget* wg, void* v)
{

	ServerTab* serverTab = (ServerTab*)v;
	if(serverTab->state.running)
		return;
	if (serverTab->state.server == nullptr)
	{
		serverTab->state.createServer("3000",serverTab->chat->tBuffer);
	}
	serverTab->bBar->serverStatus->label("online");
	serverTab->bBar->serverStatus->box(FL_FLAT_BOX);
	serverTab->bBar->serverStatus->color(FL_GREEN);
}

void GUI::ServerTab::stop_cb(Fl_Widget* wg, void* v)
{
	ServerTab* serverTab = (ServerTab*)v;
	if(!serverTab->state.running)
		return;

	serverTab->state.endServer();
	serverTab->bBar->serverStatus->label("offline");
	serverTab->bBar->serverStatus->box(FL_FLAT_BOX);
	serverTab->bBar->serverStatus->color(FL_GRAY);
	
}
void GUI::ServerTab::input_cb(Fl_Widget* wg, void* v)
{
	((ChatWindow*)v)->tBuffer->append(((Fl_Input*)wg)->value());
	((ChatWindow*)v)->tBuffer->append(" \n");
	((Fl_Input*)wg)->value("");
}

///////////////////////////////////////////////////////////////////////// chat window
GUI::ChatWindow::ChatWindow(int x, int y, int w, int h, const char* label)
    : Fl_Text_Display(x, y, w, h, label)
    , tBuffer(new Fl_Text_Buffer())
    , sBuffer(new Fl_Text_Buffer())
{
	buffer(tBuffer);
	box(FL_DOWN_BOX);
	end();
}
///////////////////////////////////////////////////////////////////////// user list
GUI::UserList::UserList(int x, int y, int w, int h)
    : Fl_Browser(x, y, w, h)
{
	type(FL_SELECT_BROWSER);
}
