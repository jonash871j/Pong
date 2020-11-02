#pragma once
#include "Sprite.h"

class Scene : Import
{
private:
	char fileformat[3] = { 0 };
	char** mapPixelArray;
	int width, height;
	int cellWidth, cellHeight;

	//void DeleteArrays();

public:
	Sprite tileSprite = { 0, 0, 0 };
	std::vector<char> listID;

	Scene(int width, int height, int spriteWidth, int spriteHeight, int cellWidth, int cellHeight);
	Scene() {};
	// Used to import map
	void ImportMap(std::string filename);

	// *******************************
	void UpdatePixelArray();

	// Scene set section *********************************************

	// Used to set a character ID for a sprite in map
	void SetSpriteID(char charID, Sprite sprite);

	// Used to set tile in map
	void SetTile(int x, int y, char character);
	
	// Scene get section *********************************************

	char GetArray readonly_2D mapArray[y][x] rs
	char GetFullArray readonly_2D mapPixelArray[y][x] rs
	int GetWidth readonly width rs
	int GetHeight readonly height rs
	int GetCellWidth readonly cellWidth rs
	int GetCellHeight readonly cellHeight rs
};
