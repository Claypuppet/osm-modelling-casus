/*
 * CUI.cpp
 *
 *  Created on: 24 Oct 2017
 *      Author: Vuurvlieg
 */

#include "CUI.h"


namespace cui
{

Window::~Window()
{
	release();
}

Window& Window::operator=(WINDOW* window)
{
	if(window != mWindow) {
		release();
		mWindow = window;
	}
	return *this;
}

bool Window::create(int nlines, int ncols, int begin_y, int begin_x)
{
	release();
	mWindow = newwin(nlines, ncols, begin_x, begin_y);
	return mWindow != NULL;
}

void Window::refresh()
{
	wrefresh(mWindow);
}

void Window::setCursor(int x, int y)
{
	wmove(mWindow, x, y);
}

int Window::getChar()
{
	return wgetch(mWindow);
}

int Window::getChar(int x, int y)
{
	return mvwgetch(mWindow, x, y);
}

int Window::outStr(const std::string& text)
{
	return waddstr(mWindow, text.c_str());
}

int Window::outStr(const std::string& text, int y, int x)
{
	return mvwaddstr(mWindow, y, x, text.c_str());
}

int Window::outStr(const std::string& text, int y, int x, int max)
{
	return mvwaddnstr(mWindow, y, x, text.c_str(), max);
}

int Window::box(chtype verch, chtype horch)
{
	return ::box(mWindow, verch, horch);
}

int Window::getInputStr(std::string& input)
{
	char buf[1024] = {};
	int err = wgetnstr(mWindow, buf, sizeof(buf) - 1);
	if(err)
		buf[0] = 0;
	input = std::string(buf);
	return err;
}

void cui::Window::release()
{
	if(mWindow) {
		delwin(mWindow);
		mWindow = NULL;
	}
}

CUI::CUI()
{
	// TODO Auto-generated constructor stub

}

CUI::~CUI()
{
	// TODO Auto-generated destructor stub
}

void CUI::initialize()
{
	mMainWnd = initscr();
	start_color();
	noecho();
	cbreak();
	curs_set(0);
	resize_term(40, 90);
	showDefaultScreen();
}

void CUI::cleanup()
{
	endwin();
}

void CUI::showDefaultScreen()
{
	mMainWnd.outStr("Hello");
	mMainWnd.refresh();
}

int CUI::setColorPair(short index, Color foreground, Color backgrnd)
{
	return ::init_pair(index, (short)foreground, (short)backgrnd);
}

void CUI::update()
{

}

}
