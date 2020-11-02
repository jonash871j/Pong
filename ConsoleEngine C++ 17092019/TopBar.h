#pragma once
#include "Variables.h"

// TopBar
void TopBar()
{
	for (int i = 0; i < topMenuLength; i++)
		console.WriteString(topMenu[i].length() * i, 0, topMenu[i], LEFT_TO_RIGHT, WHITE);

	draw.Line(0, 1, screenWidth, 1, 196, WHITE);
}