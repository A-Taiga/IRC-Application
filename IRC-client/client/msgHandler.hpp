#ifndef MSGHANDLER_HPP
#define MSGHANDLER_HPP
#include "FL/Fl.H"
#include <FL/Fl_Widget.H>
#include "client.hpp"


namespace IRC 
{
	class State 
	{
		public:
		Client& client;
		State(Client& c);
		
	};

} // namespace IRC

#endif