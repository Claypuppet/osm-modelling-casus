/*
 * Windoww.cpp
 *
 *  Created on: 1 Nov 2017
 *      Author: Vuurvlieg
 */

#include "Windoww.h"
#include "CUI.h"

#include <stdarg.h>
#include <cmath>

namespace cui {

Window& Window::setKeypad(bool bEnabled)
{
	::keypad(wptr(), bEnabled);
	return *this;
}

Window::Window(CUI& cui, WINDOWPtr window)
: 	mCUI(cui)
, 	mWindow(window)
,	mNeedRefresh(false)
{
}

void Window::update()
{
	if(mNeedRefresh)
		refresh();
}

Window& Window::refresh()
{
	wrefresh(wptr());
	mNeedRefresh = false;
	return *this;
}

Window& Window::redraw()
{
	redrawwin(wptr());
	return *this;
}

bool Window::resize(int width, int height)
{
	return noError(wresize(wptr(), height, width));
}


Window& Window::clear()
{
	wclear(wptr());
	return *this;
}

Window& Window::erase()
{
	werase(wptr());
	return *this;
}


Window& Window::moveCursor(int x, int y)
{
	if(noError(wmove(wptr(), y, x)))
		mNeedRefresh = true;
	return *this;
}

Window& Window::getCursor(int& x, int& y)
{
	x = getbegx(wptr());
	y = getbegy(wptr());
	return *this;
}

int Window::getCursorX()
{
	return getbegx(wptr());
}

int Window::getCursorY()
{
	return getbegy(wptr());
}

int Window::getChar()
{
	return wgetch(wptr());
}

int Window::getChar(int x, int y)
{
	return mvwgetch(wptr(), y, x);
}

Window& Window::str(const std::string& text)
{
	if(noError(waddstr(wptr(), text.c_str())))
		mNeedRefresh = true;
	return *this;
}

Window& Window::str(const std::string& text, int x, int y)
{
	x = adjustForStrAlignmentX(x, getWidth(), text.size());
	if(noError(mvwaddstr(wptr(), y, x, text.c_str())))
		mNeedRefresh = true;
	return *this;
}

Window& Window::str(const std::string& text, int x, int y, int max)
{
	if(noError(mvwaddnstr(wptr(), y, x, text.c_str(), max)))
		mNeedRefresh = true;
	return *this;
}


Window& Window::str(int x, int y, int max, const std::string& format, ...)
{
	moveCursor(x, y);
	if(max <= 0)
		return *this;
	va_list vl;
	va_start(vl, format);
	char buffer[1024];
	int err = std::vsnprintf(buffer, sizeof(buffer)-1, format.c_str(), vl);
	buffer[std::min((int)sizeof(buffer)-1, max)] = 0;
	va_end(vl);
	return err <= 0 ? *this : str(buffer, x, y, max);
}

Window& Window::str(int x, int y, const std::string& format, ...)
{
	moveCursor(x, y);
	va_list vl;
	va_start(vl, format);
	char buffer[1024];
	int err = std::vsnprintf(buffer, sizeof(buffer)-1, format.c_str(), vl);
	va_end(vl);
	return err <= 0 ? *this : str(buffer, x, y);
}

Window& Window::str(int max, const std::string& format, ...)
{
	if(max <= 0)
		return *this;
	va_list vl;
	va_start(vl, format);
	char buffer[1024];
	int err = std::vsnprintf(buffer, sizeof(buffer)-1, format.c_str(), vl);
	buffer[std::min((int)sizeof(buffer)-1, max)] = 0;
	va_end(vl);
	return err <= 0 ? *this : str(buffer);
}

size_t Window::inputStr(std::string& input)
{
	char buf[1024];
	int err = wgetnstr(wptr(), buf, sizeof(buf) - 1);
	if(err)
		buf[0] = 0;
	input = std::string(buf);
	return err ? 0 : input.length();
}


Window& Window::attrOn(Attr attr)
{
	if(noError(wattr_on(wptr(), static_cast<attr_t>(attr), nullptr)))
		mNeedRefresh = true;
	return *this;
}


Window& Window::attrOff(Attr attr)
{
	if(noError(wattr_off(wptr(), static_cast<attr_t>(attr), nullptr)))
		mNeedRefresh = true;
	return *this;
}

Window& Window::attrSet(Attr attr)
{
	attr_t a;
	ColorPairIndex cpi;
	if(noError(wattr_get(wptr(), &a, &cpi, nullptr))) {
		if(noError(wattr_set(wptr(), static_cast<attr_t>(attr), cpi, nullptr)))
			mNeedRefresh = true;
	}
	return *this;
}

Attr Window::attrGet()
{
	attr_t a;
	ColorPairIndex cpi;
	if(noError(wattr_get(wptr(), &a, &cpi, nullptr)))
		return static_cast<Attr>(a);
	return Attr::kAttrNormal;
}

Window& Window::setBgColors(ColorPairIndex pairIndex)
{
	if(noError(::wbkgd(wptr(), COLOR_PAIR(pairIndex))))
		mNeedRefresh = true;
	return *this;
}

Window& Window::setBgColors(const ColorPair& pair)
{
	ColorPairIndex index;
	if(mCUI.getColorPairIndex(pair,index))
		return setBgColors(index);
	return *this;
}

Window& Window::setColors(ColorPairIndex pairIndex)
{
	if(noError(wcolor_set(wptr(), pairIndex, nullptr)))
		mNeedRefresh = true;
	return *this;
}

Window& Window::setColors(const ColorPair& pair)
{
	ColorPairIndex index;
	if(mCUI.getColorPairIndex(pair,index))
		return setColors(index);
	return *this;
}

Window& Window::setFgColor(Color color)
{
	ColorPair colors = getColors();
	colors.fgColor = color;
	return setColors(colors);
}

Window& Window::setBgColor(Color color)
{
	ColorPair colors = getColors();
	colors.bgColor = color;
	return setColors(colors);
}

ColorPair Window::getColors()
{
	attr_t a;
	ColorPairIndex cpi;
	ColorPair result;
	if(noError(wattr_get(wptr(), &a, &cpi, nullptr))) {
		if(mCUI.getColorPair(cpi, result))
			return result;
	}
	return result; // wtf?
}

Color Window::getFgColor()
{
	return getColors().fgColor;
}

Color Window::getBgColor()
{
	return getColors().bgColor;
}

int Window::getWidth()
{
	return getmaxx(wptr());
}

int Window::getHeight()
{
	return getmaxy(wptr());
}

int Window::xFact(float f)
{
	int w = getWidth();
	if(w <= 0)
		return 0;
	return static_cast<int>(std::round(f * w));
}

int Window::yFact(float f)
{
	int h = getHeight();
	if(h <= 0)
		return 0;
	return static_cast<int>(std::round(f * h));
}


Window& Window::wborder()
{
	if(noError(::box(wptr(), 0, 0)))
		mNeedRefresh = true;
	return *this;
}

Window& Window::whlinea(int x1, int x2, bool mvCursor)
{
	if(x1 == x2)
		return *this;
	if(x2 < x1)
		std::swap(x1, x2);
	int w = getWidth();
	x1 = std::max(0, x1);
	x2 = std::min(w, x2);
	int cx, cy;
	getCursor(cx, cy);
	moveCursor(x1, cy);
	::whline(wptr(), 0, x2- x1);
	if(!mvCursor)
		moveCursor(cx, cy);
	return *this;
}


Window& Window::whline(int x, int dx, bool mvCursor)
{
	return whlinea(x, x + dx, mvCursor);
}

Window& Window::whline(int dx, bool mvCursor)
{
	return whline(getCursorX(), dx, mvCursor);
}

Window& Window::whline(bool mvCursor)
{
	return whline(0, getWidth(), mvCursor);
}

Window& Window::wvlinea(int y1, int y2, bool mvCursor)
{
	if(y1 == y2)
		return *this;
	if(y2 < y1)
		std::swap(y1, y2);
	int h = getHeight();
	y1 = std::max(0, y1);
	y2 = std::min(h, y2);
	int cx, cy;
	getCursor(cx, cy);
	moveCursor(cx, y1);
	::wvline(wptr(), 0, y2- y1);
	if(!mvCursor)
		moveCursor(cx, cy);
	return *this;
}

Window& Window::wvline(int y, int dy, bool mvCursor)
{
	return wvlinea(y, y + dy, mvCursor);
}

Window& Window::wvline(int dy, bool mvCursor)
{
	return wvline(getCursorY(), dy, mvCursor);
}

Window& Window::wvline(bool mvCursor)
{
	return wvline(0, getHeight(), mvCursor);
}


} /* namespace cui */


