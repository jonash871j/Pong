#include "Object.h"

Object::Object() {};

/*		 Console		*/

// Console set font
void Object::ConsoleFont(const wchar_t* fontType, byte fontSizeX, byte fontSizeY, UINT fontFamily, UINT fontWigth)
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = fontSizeX;
	cfi.dwFontSize.Y = fontSizeY;
	cfi.FontFamily = fontFamily;
	cfi.FontWeight = fontWigth;
	wcscpy_s(cfi.FaceName, fontType);
	SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
}

void ConsolePalette(byte palleteType)
{

}
