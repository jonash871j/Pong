#include "Console.h"
#include <wtypes.h>
#include <thread>
#include <conio.h>

#define SCREENWIDTH_ screenWidth
#define SCREENHEIGHT_ screenHeight

// Used to write character form array in diferent directions
#define SWITCH_WRITECHAR_DIRECTION switch (direction) {\
							       	case 0: WriteChar(x + i, y, charArray[i], color); break; \
							       	case 1: WriteChar(x - i, y, charArray[i], color); break; \
							       	case 2: WriteChar(x, y + i, charArray[i], color); break; \
							       	case 3: WriteChar(x, y - i, charArray[i], color); break; }
#pragma region PRIVATE
	int fps, fpsCount, fpsSubtrack, fpsCurrent;
	short SCREENWIDTH_, SCREENHEIGHT_;

	// Console variables from the windows libery
	CHAR_INFO* screen;
	HANDLE hConsole;
	CONSOLE_SCREEN_BUFFER_INFOEX csbiInfo;
	CONSOLE_CURSOR_INFO cursorInfo;
	CONSOLE_FONT_INFOEX cfi;
	SMALL_RECT m_rectWindow;
	WORD attribute;

	Import import;

	// FPS timer
	using namespace std::literals::chrono_literals;
	auto start = std::chrono::high_resolution_clock::now();

	// Used to update all console data like font, color and window size
	void UpdateData(bool noColorChange)
	{
		// Hide console cursor
		GetConsoleCursorInfo(hConsole, &cursorInfo);
		cursorInfo.bVisible = false;
		SetConsoleCursorInfo(hConsole, &cursorInfo);

		// Update console data
		if (noColorChange == true)
			GetConsoleScreenBufferInfoEx(hConsole, &csbiInfo);
		csbiInfo.wPopupAttributes = 0;
		csbiInfo.srWindow = { 0, 0, SCREENWIDTH_, SCREENHEIGHT_ };
		csbiInfo.dwSize = { SCREENWIDTH_, SCREENHEIGHT_ };
		csbiInfo.wAttributes = attribute;
		SetConsoleScreenBufferInfoEx(hConsole, &csbiInfo);
	}

	// Used to update the FPS in the console
	void UpdateFPS()
	{
		// Calculate fps
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> duration = end - start;
		fpsCount = duration.count() - fpsSubtrack;
		fps += 1;

		if (fpsCount >= 1)
		{
			fpsCurrent = fps;
			fpsSubtrack += fpsCount;
			fpsCount = 0;
			fps = 0;
		}
	}
#pragma endregion

#pragma region PUBLIC
// Console general section ******************************************

// Used to start the console engine and set screen dimensions
void Console::Create(short ScreenWidth, short ScreenHeight)
{
	// Sets screen dimensions
	SCREENWIDTH_ = ScreenWidth;
	SCREENHEIGHT_ = ScreenHeight;

	hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	screen = new CHAR_INFO[SCREENWIDTH_ * SCREENHEIGHT_];

	// Set consolebuffer size and screen dimensions
	SetConsoleActiveScreenBuffer(hConsole);
	m_rectWindow = { 0, 0, SCREENWIDTH_, SCREENHEIGHT_ };

	// Update all console data 
	UpdateData(true);
}


// Used to update the console
void Console::Update()
{
	// Updates screen
	WriteConsoleOutput(hConsole, screen, { SCREENWIDTH_, SCREENHEIGHT_ }, { 0, 0 }, &m_rectWindow);
	
	// Updates FPS
	UpdateFPS();

	// Update all console data 
	UpdateData(true);
}

// Used to destroy the console engine
void Console::Destroy()
{
	SetConsoleActiveScreenBuffer(hConsole);
	delete[] screen;
}

// Console write section ********************************************

// Used to write a character to the console
void Console::WriteChar(int x, int y, char character, char color)
{
	if ((y < SCREENHEIGHT_) && (y >= 0) && (x < SCREENWIDTH_) && (x >= 0))
	{
		screen[y * SCREENWIDTH_ + x].Attributes = unsigned char(color);
		screen[y * SCREENWIDTH_ + x].Char.AsciiChar = unsigned char(character);
	}
}

// Write string to screen
void Console::WriteString(int x, int y, std::string text, char direction, char color)
{
	std::vector<char> charArray(text.begin(), text.end());
	charArray.push_back('\0');

	// Draw string to screen
	for (int i = 0; i < text.length(); i++)
		SWITCH_WRITECHAR_DIRECTION
}

// Write int to screen
void Console::WriteInt(int x, int y, int intValue, char direction, char color)
{
	int intArrayLength = 0;
	std::vector <int> intArray = IntegerToArray(abs(intValue));
	std::vector <char> charArray(intArray.size());

	// If value is negative
	if (intValue < 0)
	{
		WriteChar(x, y, '-', color);
		switch (direction) {
		case tLEFTRIGHT: x += 1; break;
		case tRIGHTLEFT: x -= 1; break;
		case tTOPBUTTOM: y += 1; break;
		case tBUTTOMTOP: y -= 1; break;
		}
	}

	// Draw int to screen
	for (int i = 0; i < intArray.size(); i++){
		charArray[i] = intArray[i] + 48;
		SWITCH_WRITECHAR_DIRECTION
	}
}

// Console set section **********************************************

// Console set font
void Console::SetFont(const wchar_t* fontType, char fontSizeX, char fontSizeY)
{
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = fontSizeX;
	cfi.dwFontSize.Y = fontSizeY;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, fontType);
	SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
}

// Used to set a color palette for the console
void Console::SetColorPalette(ColorPalette colorPalette)
{
	// Sets colors
	csbiInfo.cbSize = sizeof(csbiInfo);
	GetConsoleScreenBufferInfoEx(hConsole, &csbiInfo);
	for (int y = 0; y < 16; y++)
		csbiInfo.ColorTable[y] = RGB(colorPalette.GetColorPalette(0, y), colorPalette.GetColorPalette(1, y), colorPalette.GetColorPalette(2, y));
	UpdateData(false);
}

// Console set RGB color
void Console::SetColorRGB(char id, char red, char green, char blue)
{
	// Sets colors
	csbiInfo.cbSize = sizeof(csbiInfo);
	GetConsoleScreenBufferInfoEx(hConsole, &csbiInfo);
	csbiInfo.ColorTable[id] = RGB(red, green, blue);
	UpdateData(false);
}

// Set top window text
void Console::SetWindowTitle(std::string text)
{
	SetConsoleTitle(text.c_str());
}

// Console get section **********************************************

int Console::GetFPS()          { return fpsCurrent;   }
int Console::GetScreenWidth()  { return SCREENWIDTH_;  }
int Console::GetScreenHeight() { return SCREENHEIGHT_; }
#pragma endregion

void Delay(int delay)
{
	Sleep(delay);
}