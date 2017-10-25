/*
 * CUI.h
 *
 *  Created on: 24 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef CUI_H_
#define CUI_H_

//#include <curses/curses.h>
#include <curses.h>
//#include <string>

namespace cui
{

	enum Color {
		kColorBlack = COLOR_BLACK,
		kColorRed = COLOR_RED,
		kColorGreen = COLOR_GREEN,
		kColorBlue = COLOR_BLUE,
		kColorCyan = COLOR_CYAN,
		kColorMagenta = COLOR_MAGENTA,
		kColorYellow = COLOR_YELLOW,
		kCOlorWhite = COLOR_WHITE
	};


	struct CCharL {
		CCharL()
		:_value(0)
		{
		}

		union {
			struct {
				long chr : 16;
				long altCharset : 1;
				long rightLine : 1;
				long leftLine : 1;
				long invisible : 1;
				long underline : 1;
				long reverse : 1;
				long blink : 1;
				long bold : 1;
				long color : 8;
			};
			long _value;
		};


		operator chtype() {
			return (chtype)_value;
		}
	};

	struct Window
	{
		Window() : mWindow(NULL) {}
		Window(WINDOW* window)
		:	mWindow(window) {}

		~Window();

		Window& operator=(WINDOW* window);

		bool create(int nlines, int ncols, int begin_y, int begin_x);
		void refresh();


		void setCursor(int x, int y);

		int getChar();
		int getChar(int x, int y);



		int outStr(const std::string& text);
		int outStr(const std::string& text, int y, int x);
		int outStr(const std::string& text, int y, int x, int max);

		int getInputStr(std::string& input);

		int box(chtype verch, chtype horch);

		void release();



	private:
		WINDOW*	mWindow;
	};


	class CUI
	{
	public:


	public:
		CUI();
		~CUI();

		void initialize();
		void cleanup();

		void update();

		void showDefaultScreen();


		int setColorPair(short index, Color foreground, Color backgrnd);


	private:
		Window	mMainWnd;
	};
}



#endif /* CUI_H_ */
