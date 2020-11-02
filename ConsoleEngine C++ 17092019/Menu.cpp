#include "Menu.h"
#include "Engine.h"

void Menu::CursorFadeEffect()
{
	// Menu cursor blinking
	fCount += 0.03;
	fVal = (sin(fCount) * 175);
	if (fVal <= 0) {
		fVal = 0;
		fCount = 0;
	}
	Console::SetColorRGB(8, 0, fVal + 80, fVal + 80);
}

Menu::Menu(std::vector<std::string> menu) : menu(menu) {}

void Menu::Drawing()
{
	// Cursor fade effect
	CursorFadeEffect();

	// Input menu
	if ((Input::KeyPressed(VK_UP)) && (cPos > 0)){
		cPos--;
	
		Sound::Play("./Sound/sndNoise");
	}

	if ((Input::KeyPressed(VK_DOWN)) && (cPos < menu.size() - 1)) {
		cPos++;
		Sound::Play("./Sound/sndNoise");
	}

	if (Input::KeyReleased(VK_RETURN))
		cClicked = cPos;
	else
		cClicked = -1;


	// Draw menu
	Draw::Rectangle(XMID - 20, YMID - 4, XMID + 20, YMID + (5 * menu.size()), 219, BLACK, false);
	Draw::Rectangle(XMID - 20, YMID - 4, XMID + 20, YMID + (5 * menu.size()), 219, WHITE, true);
	for (int i = 0; i < menu.size(); i++) {
		if (i == cPos)
			Draw::Text(fntNormal, XMID - (menu[i].length() * 2) + 1, (i * 5) + YMID, menu[i], 0, D_GREY);
		else
			Draw::Text(fntNormal, XMID - (menu[i].length() * 2) + 1, (i * 5) + YMID, menu[i], 0, WHITE);
	}
}