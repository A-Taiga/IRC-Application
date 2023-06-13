#include "tempArea.hpp"
#include "FL/Enumerations.H"
#include "FL/Fl.H"
#include "FL/Fl_Group.H"
#include "FL/Fl_Input.H"
#include "FL/Fl_Text_Buffer.H"
#include "FL/Fl_Text_Display.H"
#include "FL/Fl_Widget.H"



struct thing 
{
	Fl_Text_Buffer* buffer;
	IRC::State* state;
};

GUI::Group::Group(int x, int y, int w, int h, IRC::State& s)
: Fl_Group(x, y, w, h)
, state(s)
{
	buffer = new Fl_Text_Buffer();
	display = new Fl_Text_Display(x,y,w,h-40);
	display->buffer(buffer);
	display->end();
	
	input = new Fl_Input(x,y + display->h()+10, display->w(), 30);
	input->callback(input_cb,new thing{buffer,&state});
	input->when(FL_WHEN_ENTER_KEY);
	end();
}
void GUI::Group::input_cb(Fl_Widget* wg, void* v)
{
	std::string msg = ((Fl_Input*)wg)->value();
	((thing*)v)->buffer->append(((Fl_Input*)wg)->value());
	((thing*)v)->buffer->append(" \n");
	int fd = ((thing*)v)->state->client.socket_fd;
	::send(fd,msg.data(),msg.size(),0);
	((Fl_Input*)wg)->value("");

}

