/*
 * Windoww.h
 *
 *  Created on: 1 Nov 2017
 *      Author: Vuurvlieg
 */

#ifndef CUI_WINDOWW_H_
#define CUI_WINDOWW_H_

#include "Core.h"
#include <memory>
#include <string>

namespace cui
{

	class CUI;

	class Window
	{
			typedef WINDOW *PWINDOW;
			typedef std::shared_ptr<WINDOW> WINDOWPtr;

			struct AttrScope {
				AttrScope(Window& w)
				: w(w)
				, a(0)
				, cpi(0)
				{
					wattr_get(w.wptr(), &a, &cpi, nullptr);
				}
				~AttrScope() { restore(); }
				void restore() { wattr_set(w.wptr(),a, cpi, nullptr); }
			private:
				Window& w;
				attr_t a;
				ColorPairIndex cpi;

			};

		public:
			Window(const Window& other) = default;
			~Window() = default;

			Window& operator=(const Window& other) = default;
			bool operator==(const Window& other) const { return mWindow == other.mWindow; }

			PWINDOW wptr() { return mWindow.get(); }
			explicit operator PWINDOW() { return mWindow.get(); }

			void update();

			Window& refresh();
			Window& redraw();
			Window& clear();
			Window& erase();


			bool resize(int width, int height);
			int getWidth();
			int getHeight();

			int xFact(float f);
			int yFact(float f);


			Window& attrOn(Attr attr);
			Window& attrOff(Attr attr);
			Window& attrSet(Attr attr);
			Attr	attrGet();

			Window&	setBgColors(ColorPairIndex pairIndex);
			Window& setBgColors(const ColorPair& pair);
			Window& setColors(ColorPairIndex pairIndex);
			Window& setColors(const ColorPair& pair);
			Window& setFgColor(Color color);
			Window& setBgColor(Color color);
			ColorPair getColors();
			Color getFgColor();
			Color getBgColor();

			Window& setKeypad(bool bEnabled);


			Window& moveCursor(int x, int y);
			Window& getCursor(int& x, int& y);
			int getCursorX();
			int getCursorY();


			int getChar();
			int getChar(int x, int y);



			Window& str(const std::string& text);
			Window& str(const std::string& text, int x, int y);
			Window& str(const std::string& text, int x, int y, int max);
			Window& str(int x, int y, int max, const std::string& format, ...);
			Window& str(int x, int y, const std::string& format, ...);
			Window& str(int max, const std::string& format, ...);


			size_t inputStr(std::string& input);



			Window& wborder();
			Window& whlinea(int x1, int x2, bool moveCursor=false);
			Window& whline(int x, int dx, bool moveCursor=false);
			Window& whline(int dx, bool moveCursor=false);
			Window& whline(bool moveCursor=false);
			Window& wvlinea(int y1, int y2, bool moveCursor=false);
			Window& wvline(int y, int dy, bool moveCursor=false);
			Window& wvline(int dy, bool moveCursor=false);
			Window& wvline(bool moveCursor=false);





		private:
			friend CUI;
			Window(CUI& cui, WINDOWPtr window);


		private:
			CUI&		mCUI;
			WINDOWPtr	mWindow;
			bool		mNeedRefresh;
		};

} /* namespace cui */

#endif /* CUI_WINDOWW_H_ */
