#include "Draw.h"

// Defitions used in the file only
#pragma region DEFINES
#define SPRITEMATRIX_START for (int y = 0; y < sprite.GetHeight(); y++){ \
						   for (int x = 0; x < sprite.GetWidth(); x++) { \
			               if (sprite.GetCharacterArray(x, y) != NULL)
#define SPRITEMATRIX_STOP }}
#define SPRITE sprite.GetCharacterArray(x, y), sprite.GetColorArray(x, y)
#define RX (-x + sprite.GetWidth() - 1)  // Current draw sprite x postion reversed
#define RY (-y + sprite.GetHeight() - 1) // Current draw sprite y postion reversed

#define X_OBJ xOff + object.GetXPos()	 // Current draw object x postion
#define Y_OBJ yOff + object.GetYPos()	 // Current draw object y postion

// Used to write character form array in diferent directions
#define SWITCH_WRITECHAR_DIRECTION switch (direction) {\
							       	case tLEFTRIGHT: Text(font, x + (i * (font.GetWidth() + 1)), y, charArray[i], color); break; \
							       	case tRIGHTLEFT: Text(font, x - (i * (font.GetWidth() + 1)), y, charArray[i], color); break; \
							       	case tTOPBUTTOM: Text(font, x, y + (i * (font.GetHeight() + 1)), charArray[i], color); break; \
							       	case tBUTTOMTOP: Text(font, x, y - (i * (font.GetHeight() + 1)), charArray[i], color); break; }

#define MAPMATRIX_START for (int y = 0; y < scene.GetHeight(); y++){ \
							for (int x = 0; x < scene.GetWidth(); x++)
#define MAPMATRIX_STOP }		            
#pragma endregion

// Draw font section *************************************************

// Used to draw a char with a font
void Draw::Text(Font font, int x, int y, char character, char color)
{
	font.GetSprite().ImportLayer(font.GetSpritePath(character), 0);
	Draw::SpriteSingleColor(font.GetSprite(), x, y, color);
}

// Used to draw a string with a font
void Draw::Text(Font font, int x, int y, std::string text, char direction, char color)
{
	std::vector<char> charArray(text.begin(), text.end());
	charArray.push_back('\0');

	// Draw string to screen
	for (int i = 0; i < text.length(); i++)
		SWITCH_WRITECHAR_DIRECTION
}

// Used to draw a int with a font
void Draw::Text(Font font, int x, int y, int intValue, char direction, char color)
{
	int intArrayLength = 0;
	std::vector <int> intArray = IntegerToArray(abs(intValue));
	std::vector <char> charArray(intArray.size());

	// If value is negative
	if (intValue < 0)
	{
		Text(font, x, y, '-', color);
		switch (direction) {
		case tLEFTRIGHT: x += font.GetWidth() + 1;  break;
		case tRIGHTLEFT: x -= font.GetWidth() + 1;  break;
		case tTOPBUTTOM: y += font.GetHeight() + 1; break;
		case tBUTTOMTOP: y -= font.GetHeight() + 1; break;
		}
	}
	// Draw int to screen
	for (int i = 0; i < intArray.size(); i++) {
		charArray[i] = intArray[i] + 48;
		SWITCH_WRITECHAR_DIRECTION
	}
}

// Draw scene section

// Used to draw map of scene in full scale
void Draw::Map(Scene scene, int xOff, int yOff)
{
	MAPMATRIX_START
	{
		for (int i = 0; i < scene.listID.size(); i++) {
			if (scene.GetArray(x, y) == scene.listID[i]){
				scene.tileSprite.ChangeSpriteLayer(scene.listID[i]);
				Draw::SpritePlain(scene.tileSprite, (x * scene.GetCellWidth() + xOff), (y * scene.GetCellHeight() + yOff));
			}
		}
	}
	MAPMATRIX_STOP
}

// Used to draw map array of scene
void Draw::MapArray(Scene scene, int xOff, int yOff, char color)
{
	MAPMATRIX_START{ Console::WriteChar(x + xOff, y + yOff, scene.GetArray(x, y), color); }MAPMATRIX_STOP
}

// Draw sprite section ***********************************************

// Used to draw sprite
void Draw::SpritePlain(Sprite sprite, int xPos, int yPos)
{
	SPRITEMATRIX_START{ Console::WriteChar(x + xPos, y + yPos, SPRITE); }SPRITEMATRIX_STOP
}
void Draw::SpritePlain(Object object, int xOff, int yOff)
{ Draw::SpritePlain(object.sprite, X_OBJ, Y_OBJ);}

// Used to draw sprite that can flip and rotate
void Draw::SpriteDirection(Sprite sprite, int xPos, int yPos, bool flip, int rotation)
{
	SPRITEMATRIX_START
	{
		switch (flip)
		{
		case true:
			switch (rotation) {
			case 0: Console::WriteChar(x + xPos, y + yPos, SPRITE);     break;
			case 180: Console::WriteChar(RX + xPos, RY + yPos, SPRITE); break;
			case 90: Console::WriteChar(yPos + xPos, x + yPos, SPRITE); break;
			case 270: Console::WriteChar(y + yPos, RX + yPos, SPRITE);  break;
			}break;
		case false:
			switch (rotation) {
			case 0: Console::WriteChar(x + xPos, RY + yPos, SPRITE);    break;
			case 180: Console::WriteChar(RX + xPos, y + yPos, SPRITE);  break;
			case 90: Console::WriteChar(y + xPos, x + yPos, SPRITE);    break;
			case 270: Console::WriteChar(RY + xPos, RX + yPos, SPRITE); break;
			}break;
		}
	}
	SPRITEMATRIX_STOP
}
void Draw::SpriteDirection(Object object, int xOff, int yOff)
{ Draw::SpriteDirection(object.sprite, X_OBJ, Y_OBJ, object.GetFlip(), object.GetRoation());}

// Used to draw sprite that only haves a single color
void Draw::SpriteSingleColor(Sprite sprite, int xPos, int yPos, char color)
{
	SPRITEMATRIX_START{ Console::WriteChar(x + xPos, y + yPos, sprite.GetCharacterArray(x, y), color); }SPRITEMATRIX_STOP
}
void Draw::SpriteSingleColor(Object object, int xOff, int yOff, char color)
{ Draw::SpriteSingleColor(object.sprite, X_OBJ, Y_OBJ, color); }

// Used to draw sprite that only haves a single character
void Draw::SpriteSingleCharacter(Sprite sprite, int xPos, int yPos, char character)
{
	SPRITEMATRIX_START{ Console::WriteChar(x + xPos, y + yPos, character, sprite.GetColorArray(x, y)); }SPRITEMATRIX_STOP
}
void Draw::SpriteSingleCharacter(Object object, int xOff, int yOff, char character)
{Draw::SpriteSingleCharacter(object.sprite, X_OBJ, Y_OBJ, character);}

// Used to draw sprite that only haves a single character and color
void Draw::SpriteShape(Sprite sprite, int xPos, int yPos, char character, char color)
{
	SPRITEMATRIX_START{ Console::WriteChar(x + xPos, y + yPos, character, color); }SPRITEMATRIX_STOP
}
void Draw::SpriteShape(Object object, int xOff, int yOff, char character, char color)
{Draw::SpriteShape(object.sprite, X_OBJ, Y_OBJ, character, color);}

// Used to draw a background with sprite
void Draw::SpriteBackground(Sprite sprite)
{
	for (int yB = 0; yB < ceil(SCREENHEIGHT / sprite.GetHeight()); yB++) {
		for (int xB = 0; xB < ceil(SCREENWIDTH / sprite.GetWidth()); xB++) {
			SPRITEMATRIX_START{
				Console::WriteChar(x + (xB * sprite.GetWidth()), y + (yB * sprite.GetHeight()), SPRITE);
			}SPRITEMATRIX_STOP
		}
	}
}

// Draw shape section ***********************************************

// Used to draw a background 
void Draw::Background(char character, char color)
{
	for (int y = 0; y < SCREENHEIGHT; y++)
		for (int x = 0; x < SCREENWIDTH; x++)
			Console::WriteChar(x, y, character, color);
}

// Used to draw a rectanlge
void Draw::Rectangle(int x1, int y1, int x2, int y2, char character, char color, bool outline)
{
	// Swap values if the first value is negative
	if (x2 < x1) std::swap(x2, x1);
	if (y2 < y1) std::swap(y2, y1);

	// Draw rectangle
	for (int y = y1; y <= y2; y++) {
		for (int x = x1; x <= x2; x++) {
			// Rectangle fill
			if (outline == false)
				Console::WriteChar(x, y, character, color);
			// Rectangle Outline
			else if ((x == x1) || (y == y1) || (x == x2) || (y == y2))
				Console::WriteChar(x, y, character, color);
		}
	}
}

// Used to draw a line
void Draw::Line(int x1, int y1, int x2, int y2, char character, char color)
{
	int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
	dx = x2 - x1; dy = y2 - y1;
	dx1 = abs(dx); dy1 = abs(dy);
	px = 2 * dy1 - dx1;	py = 2 * dx1 - dy1;

	if (dy1 <= dx1)
	{
		if (dx >= 0) { x = x1; y = y1; xe = x2; }
		else { x = x2; y = y2; xe = x1; }

		Console::WriteChar(x, y, character, color);

		for (i = 0; x < xe; i++){
			x = x + 1;
			if (px < 0) px = px + 2 * dy1;
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) y = y + 1; else y = y - 1;
				px = px + 2 * (dy1 - dx1);
			}
			Console::WriteChar(x, y, character, color);
		}
	}
	else
	{
		if (dy >= 0) { x = x1; y = y1; ye = y2; }
		else { x = x2; y = y2; ye = y1; }

		Console::WriteChar(x, y, character, color);

		for (i = 0; y < ye; i++)
		{
			y = y + 1;
			if (py <= 0) py = py + 2 * dx1;
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) x = x + 1;
				else x = x - 1;
				py = py + 2 * (dx1 - dy1);
			}
			Console::WriteChar(x, y, character, color);
		}
	}
}

// 
void Draw::Triangle(int x1, int y1, int x2, int y2, int x3, int y3, char character, char color)
{
	Draw::Line(x1, y1, x2, y2, character, color);
	Draw::Line(x2, y2, x3, y3, character, color);
	Draw::Line(x3, y3, x1, y1, character, color);
}

// Used to draw a circle
void Draw::Circle(int x, int y, int radius, char character, char color)
{
	int _x = 0;
	int _y = radius;
	int pi = 3 - 2 * radius;
	if (!radius)
		return;

	while (_y >= _x) // only formulate 1/8 of circle
	{
		Console::WriteChar(x - _x, y - _y, character, color); //upper left left
		Console::WriteChar(x - _y, y - _x, character, color); //upper upper left
		Console::WriteChar(x + _y, y - _x, character, color); //upper upper right
		Console::WriteChar(x + _x, y - _y, character, color); //upper right right
		Console::WriteChar(x - _x, y + _y, character, color); //lower left left
		Console::WriteChar(x - _y, y + _x, character, color); //lower lower left
		Console::WriteChar(x + _y, y + _x, character, color); //lower lower right
		Console::WriteChar(x + _x, y + _y, character, color); //lower right right
		if (pi < 0) pi += 4 * _x++ + 6;
		else pi += 4 * (_x++ - _y--) + 10;
	}
}

// Used to draw a parabola
void Draw::Parabola(int x1, int y1, bool center, float a, float b, float c, float accuracy, char character, char color)
{
	for (float y = -YMID - y1; y < YMID - y1; y += accuracy) {
		for (float x = -XMID + x1; x < XMID + x1; x += accuracy) {
			if (((a * pow(x, 2)) + (b * x) + c <= y + accuracy) && ((a * pow(x, 2)) + (b * x) + c >= y - accuracy))
			{
				if (center == false) Console::WriteChar(roundf(x) + x1, -roundf(y) - y1, character, color);
				else Console::WriteChar(roundf(x) + x1 + XMID, -roundf(y) - y1 + YMID, character, color);
			}
		}
	}
}