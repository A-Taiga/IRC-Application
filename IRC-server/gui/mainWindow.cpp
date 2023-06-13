#include "mainWindow.hpp"
#include "bottomBar.hpp"
#include "state.hpp"
#include "topBar.hpp"

GUI::MainWindow::MainWindow(int w, int h, const char* label)
    : Fl_Window(w, h, label)
	, state()
{
	topBar = new TopBar(0, 0, w, 30);
	bBar   = new BottomBar(0, h - 30, w, 30);
	tabs   = new Tabs(0, topBar->h(), w, h - topBar->h() - bBar->h(), this->bBar,state);
}
