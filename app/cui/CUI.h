/*
 * CUI.h
 *
 *  Created on: 24 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef CUI_H_
#define CUI_H_


#include "Windoww.h"
#include <vector>
#include <memory>
#include <list>

namespace cui
{
	class CUI
	{
	public:
		typedef std::vector<ColorPair> ColorPairVec;

	public:
		CUI();
		~CUI();



		void update();

		void showDefaultScreen();

		bool showCursor(bool veryVisible=false);
		bool hideCursor();


		Window create(int width = 0, int height = 0, int dx = 0, int dy = 0);
		bool getColorPairIndex(const ColorPair& pair, ColorPairIndex& index, bool createIfNotExist=true);
		bool getColorPair(ColorPairIndex index, ColorPair& pair);
		bool validColorPairIndex(ColorPairIndex index);
		const ColorPairVec& getAllColorPairs() const;

	private:

		void initialize();
		void cleanup();
		Window toWindow(WINDOW* window);

	private:


		Window	mMainWnd;
		ColorPairVec mColorPairs;
	};
}



#endif /* CUI_H_ */
