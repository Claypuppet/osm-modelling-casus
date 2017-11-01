/*
 * CUI.cpp
 *
 *  Created on: 24 Oct 2017
 *      Author: Vuurvlieg
 */

#include "CUI.h"
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <string>
#include <iterator>
#include <stdexcept>
#include <algorithm>

namespace cui {


CUI::CUI()
: 	mMainWnd{toWindow(initscr())}
{
	initialize();
}

CUI::~CUI()
{
	cleanup();
}

void CUI::initialize()
{
	start_color();
	noecho();
	cbreak();
	hideCursor();
	//resize_term(40, 90);
	//mMainWnd.resize(90, 40);

	mColorPairs.clear();
	mColorPairs.push_back(ColorPair{});

	showDefaultScreen();
}

void CUI::cleanup()
{
	endwin();
}

Window CUI::toWindow(WINDOW* window)
{
	if(!window)
		throw std::invalid_argument("window == nullptr");
	return Window{*this, std::shared_ptr<WINDOW>(window, [](WINDOW* w){
			delwin(w);
	})};
}

Window CUI::create(int width, int height, int dx, int dy)
{
	return toWindow(newwin(height, width, dy, dx));
}


bool CUI::getColorPairIndex(const ColorPair& pair, ColorPairIndex& index, bool createIfNotExist)
{
	auto iter = std::find(mColorPairs.begin(), mColorPairs.end(), pair);
	if(iter != mColorPairs.end()) {
		index = static_cast<ColorPairIndex>(std::distance(mColorPairs.begin(), iter));
		return true;
	}
	if(createIfNotExist) {
		const ColorPairIndex nextIndex = static_cast<ColorPairIndex>(mColorPairs.size());
		if(index >= COLOR_PAIRS)
			return false;
		if(noError(init_pair(nextIndex, pair.fgColor, pair.bgColor))) {
			mColorPairs.push_back(pair);
			index = nextIndex;
			return true;
		}
	}
	return false;
}


void CUI::update()
{

}

bool CUI::showCursor(bool veryVisible)
{
	if(veryVisible && noError(curs_set(kCursorVisVeryVisible)))
		return true;
	return noError(curs_set(kCursorVisVisible));
}

bool CUI::hideCursor()
{
	return noError(curs_set(kCursorVisInvisible));
}

bool CUI::getColorPair(ColorPairIndex index, ColorPair& pair)
{
	if(static_cast<size_t>(index) >= mColorPairs.size()) {
		ColorPair p;
		if(noError(pair_content(index, &p.fgColor, &p.bgColor))) {
			pair = p;
			return true;
		}
		return false;
	}
	pair = mColorPairs[index];
	return true;
}


bool CUI::validColorPairIndex(ColorPairIndex index)
{
	size_t absIndex = static_cast<size_t>(index);
	if(absIndex < mColorPairs.size())
		return true;
	ColorPair p;
	return noError(pair_content(index, &p.fgColor, &p.bgColor));
}

const CUI::ColorPairVec& CUI::getAllColorPairs() const
{
	return mColorPairs;
}


void CUI::showDefaultScreen()
{
	mMainWnd.setColors(ColorPair{kColorRed, kColorBlack})
			.attrOn(Attr::kAttrStandout)
			.str(mMainWnd.xFact(0.5f) - 4, 4, "RedCars")
			.wborder()
			.refresh();
	Window wnd = create(mMainWnd.xFact(.5f), mMainWnd.yFact(.6f), mMainWnd.xFact(.25f), mMainWnd.yFact(.2f) );
	wnd.setBgColors(ColorPair{kColorYellow,kColorBlue})
			.wborder()
			.refresh();
}


}


