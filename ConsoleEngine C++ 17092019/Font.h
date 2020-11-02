#pragma once
#include "Sprite.h"

class Font
{
private:
	int width, height;
	std::string folderPath, spritePath;
	Sprite sprite = { 0, 0, 0 };
public:
	Font(std::string folderPath, int width, int height);
	~Font();

	// Returns sprite path for current font character
	std::string GetSpritePath(char character);

	// Font get section **********************************************

	int GetWidth readonly width rs
	int GetHeight readonly height rs
	Sprite GetSprite readonly sprite rs
};