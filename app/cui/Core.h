/*
 * Core.h
 *
 *  Created on: 1 Nov 2017
 *      Author: Vuurvlieg
 */

#ifndef CUI_CORE_H_
#define CUI_CORE_H_

#include <stdint.h>
#if defined(_WIN32)
//#	include <curses/curses.h>
#	include <ncursesw/curses.h>
#	include <ncursesw/menu.h>
#else
#	include <ncurses.h>
#endif
#include <algorithm>

namespace cui
{
	typedef short Color;
	typedef short ColorPairIndex;

	static const constexpr Color kColorBlack = COLOR_BLACK;
	static const constexpr Color kColorRed = COLOR_RED;
	static const constexpr Color kColorGreen = COLOR_GREEN;
	static const constexpr Color kColorBlue = COLOR_BLUE;
	static const constexpr Color kColorCyan = COLOR_CYAN;
	static const constexpr Color kColorMagenta = COLOR_MAGENTA;
	static const constexpr Color kColorYellow = COLOR_YELLOW;
	static const constexpr Color kColorWhite = COLOR_WHITE;

	static const constexpr int kError = -1;
	static const constexpr int kOK = 0;
	constexpr bool noError(int err) { return err >= 0; }

	static const constexpr int kCursorVisInvisible = 0;
	static const constexpr int kCursorVisVisible = 1;
	static const constexpr int kCursorVisVeryVisible = 0;

	static const constexpr int STR_X_HALIGN_LEFT 	= 0x8001;
	static const constexpr int STR_X_HALIGN_RIGHT 	= 0x8002;
	static const constexpr int STR_X_HALIGN_CENTRE 	= 0x8003;
	static const constexpr int STR_Y_HALIGN_LEFT 	= 0x8001;
	static const constexpr int STR_Y_HALIGN_RIGHT 	= 0x8002;
	static const constexpr int STR_Y_HALIGN_CENTRE 	= 0x8003;





	struct ColorPair  {
		ColorPair() : fgColor(kColorWhite), bgColor(kColorBlack) {}
		ColorPair(Color fgColor, Color bgColor) : fgColor(fgColor), bgColor(bgColor) {}
		bool operator==(const ColorPair& o) const {
			return o.fgColor == fgColor && o.bgColor == bgColor;
		}

		Color fgColor; // foreground
		Color bgColor; // background
	};

	enum class Attr : attr_t {
		kAttrNormal = A_NORMAL,
		kAttrStandout = A_STANDOUT,
		kAttrUnderline = A_UNDERLINE,
		kAttrReverse = A_REVERSE,
		kAttrBlink = A_BLINK,
		kAttrDim = A_DIM,
		kAttrProtect = A_PROTECT,
		kAttrInvis = A_INVIS,
		kAttrAltCharset = A_ALTCHARSET,
		kAttrItalic = A_ITALIC,
		kAttrCharText = A_CHARTEXT,
	};

	inline constexpr Attr operator|(const Attr& a, const Attr& b)
	{
		return static_cast<Attr>((size_t)a | (size_t)b);
	}



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

	constexpr int adjustForStrAlignmentX(int x, int width, size_t strlen)
	{
		if(!(x & STR_X_HALIGN_CENTRE))
			return x;
		if((x & ~STR_X_HALIGN_CENTRE))
			return x;
		int opt = x & 3;
		switch(opt) {
		default:
		case 1:
			return x;
		case 2:
			return std::max(0, width - static_cast<int>(strlen));
		case 3:
			return std::min(width, std::max(0, width / 2 - static_cast<int>(strlen) / 2));
		}
	}

}




#endif /* CUI_CORE_H_ */
