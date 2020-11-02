#pragma once
#include "EngineCore.h"

class Menu
{
private:
	std::vector<std::string> menu;
	double fVal = 1.0f;
	double fCount = 0.0f;
	int cPos = 0;
	int cClicked = -1;

private:
	void CursorFadeEffect();

public:
	Menu(std::vector<std::string> menu);
	void Drawing();

	int GetClickedPosition readonly cClicked rs
};

