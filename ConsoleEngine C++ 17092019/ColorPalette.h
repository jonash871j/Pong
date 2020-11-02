#pragma once
#include "Import.h"

class ColorPalette : Import
{
public:
	// Used to import colorpalette
	void ImportColorPalette(std::string filename);

	// Used to get value form the colorpalette, y[16] = colorID, x[3] = RGB
	char GetColorPalette readonly_2D colorPaletteArray[y][x] rs
};

