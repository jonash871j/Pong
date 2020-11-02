#pragma once
#include "Console.h"
#include "Object.h"
#include "Font.h"

namespace Draw
{
	// Draw font section *************************************************

	// Used to draw a char, string or int with a font
	void Text(Font font, int x, int y, char character, char color);
	void Text(Font font, int x, int y, std::string text, char direction, char color);
	void Text(Font font, int x, int y, int, char direction, char color);

	// Draw scene section

	// Used to draw map of scene in full scale
	void Map(Scene scene, int xOff, int yOff);

	// Used to draw map array of scene
	void MapArray(Scene scene, int xOff, int yOff, char color);


	// Draw sprite section ***********************************************

	// Used to draw sprite
	void SpritePlain(Sprite sprite, int xPos, int yPos);
	void SpritePlain(Object object, int xOff, int yOff);
	
	// Used to draw sprite of object that can flip and rotate
	void SpriteDirection(Sprite sprite, int xPos, int yPos, bool flip, int rotation);
	void SpriteDirection(Object object, int xOff, int yOff);

	// Used to draw sprite of object that only haves a single color
	void SpriteSingleColor(Sprite sprite, int xPos, int yPos, char color);
	void SpriteSingleColor(Object object, int xOff, int yOff, char color);

	// Used to draw sprite of object that only haves a single character
	void SpriteSingleCharacter(Sprite sprite, int xPos, int yPos, char character);
	void SpriteSingleCharacter(Object object, int xOff, int yOff, char character);

	// Used to draw sprite of object that only haves a single character and color
	void SpriteShape(Sprite sprite, int xPos, int yPos, char character, char color);
	void SpriteShape(Object object, int xOff, int yOff, char character, char color);

	// Used to draw a background with sprite
	void SpriteBackground(Sprite sprite);

	// Draw shape section ************************************************

	// Used to draw a background 
	void Background(char character, char color);

	// Used to draw a rectanlge
	void Rectangle(int x1, int y1, int x2, int y2, char character, char color, bool outline);

	// Used to draw a line
	void Line(int x1, int y1, int x2, int y2, char character, char color);

	// Used to draw a triangle
	void Triangle(int x1, int y1, int x2, int y2, int x3, int y3, char character, char color);

	// Used to draw a circle
	void Circle(int x, int y, int radius, char character, char color);

	// Used to draw a parabola
	void Parabola(int x1, int y1, bool center, float a, float b, float c, float accuracy, char character, char color);
}