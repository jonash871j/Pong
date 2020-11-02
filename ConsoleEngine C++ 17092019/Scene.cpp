#include "Scene.h"

Scene::Scene(int width, int height, int spriteWidth, int spriteHeight,int cellWidth, int cellHeight)
{
	this->cellWidth = cellWidth;
	this->cellHeight = cellHeight;
	this->width = width;
	this->height = height;

	// Defines the size of the sprites in sprite array
	Sprite tileSprite = { 255, spriteWidth, spriteHeight };
	this->tileSprite = tileSprite;

	// Defines the size of the map arrays
	mapArray = new char* [height];
	for (int i = 0; i < height; i++)
		mapArray[i] = new char[width];

	// Defines the size of the pixel arrays
	int mapPixelWidth = (width * cellWidth) + 1;
	int mapPixelHeight = (height * cellHeight) + 1;
	mapPixelArray = new char* [mapPixelHeight];
	for (int i = 0; i < mapPixelHeight; i++)
		mapPixelArray[i] = new char[mapPixelWidth];
}

// Private - Delete arrays
//void Scene::DeleteArrays()
//{
//	for (int i = 0; i < cellHeight; i++)
//		delete[] mapArray[i];
//	delete[] mapArray;
//}

// Used to import map
void Scene::ImportMap(std::string fileName)
{ 
	ImportMAP(fileName);
}
#pragma endregion

// Updating pixel array
void Scene::UpdatePixelArray()
{
	for (int y1 = 0; y1 < height; y1++)
		for (int x1 = 0; x1 < width; x1++)
			for (int y2 = 0; y2 < cellHeight; y2++)
				for (int x2 = 0; x2 < cellWidth; x2++)
					mapPixelArray[y2 + (y1 * cellHeight)][x2 + (x1 * cellWidth)] = mapArray[y1][x1];
}

// Used to set a character ID for a sprite in map
void Scene::SetSpriteID(char charId, Sprite sprite)
{
	tileSprite.ReplaceLayer(charId, sprite, 0);
	listID.push_back(charId);
}

// Used to set tile in map
void Scene::SetTile(int x, int y, char character)
{
	for (int y1 = 0; y1 < cellHeight; y1++)
		for (int x1 = 0; x1 < cellWidth; x1++)
			mapArray[int(y + y1) / cellHeight][int(x + x1) / cellWidth] = character;
}