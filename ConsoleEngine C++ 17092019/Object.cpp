#include "Object.h"
#include "Draw.h"

#define MATRIX_STOP }
#define SPRITEMATRIX_START for (int y = 0; y < sprite.GetHeight(); y++){ \
								  for (int x = 0; x < sprite.GetWidth(); x++)
#define SCN_CELLMATRIX_START for (int y = 0; y < scene.GetCellHeight(); y++){ \
								for (int x = 0; x < scene.GetCellWidth(); x++)



Object::Object(int spriteAmount, int width, int height)
{
	Sprite sprite = { spriteAmount, width, height };
	this->sprite = sprite;
	xPos = 0; yPos = 0;
}
Object::Object(Sprite sprite)
{
	this->sprite = sprite;
	xPos = 0; yPos = 0;
}
Object::~Object() {}

// Object events *************************************************

// Returns true if this object collides with another object
bool Object::ObjectCollide(Object object, float xOff, float yOff)
{
	float xoPos = floorf(object.xPos);
	float yoPos = floorf(object.yPos);
	float xoSize = object.sprite.GetWidth();
	float yoSize = object.sprite.GetHeight();

	SPRITEMATRIX_START{
		if ((xPos + xOff + x >= xoPos) && (xPos + xOff + x < xoPos + xoSize) &&
			(yPos + yOff + y >= yoPos) && (yPos + yOff + y < yoPos + yoSize))
			return true;
	}MATRIX_STOP
	return false;
}

// Returns true if this object collides with a tile from a scene
bool Object::TileCollide(Scene scene, char tile)
{
	SCN_CELLMATRIX_START{
		if (scene.GetArray((xPos + x) / scene.GetCellWidth(), (yPos + y) / scene.GetCellHeight()) == tile)
			return true;
	}MATRIX_STOP
	return false;
}

bool Object::TilePreciseCollide(Scene scene, float xOff, float yOff, int xSizeOff, int ySizeOff, int tile)
{
	// Avoids accessviolations
	while (yOff + yPos < 0)
		yOff += 1;
	while (xOff + xPos < 0)
		xOff += 1;
	while (yOff + yPos >= scene.GetHeight() * scene.GetCellHeight())
		yOff -= 1;
	while (xOff + xPos >= scene.GetWidth() * scene.GetCellWidth())
		xOff -= 1;

	// Collision
	for (int y = 0; y < sprite.GetHeight() + ySizeOff; y++)
		for (int x = 0; x < sprite.GetWidth() + xSizeOff; x++)
			if (scene.GetFullArray(int(xOff + xPos) + x, int(yOff + yPos) + y) == tile)
				return true;
	return false;
}

// Used to get distance to another object
float Object::ObjectDistance(Object object)
{
	float count = 0;
	int x1 = xPos + (sprite.GetWidth() / 2);
	int y1 = yPos + (sprite.GetHeight() / 2);
	int x2 = object.xPos + (object.sprite.GetWidth() / 2);
	int y2 = object.yPos + (object.sprite.GetHeight() / 2);
	int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
	dx = x2 - x1; dy = y2 - y1;
	dx1 = abs(dx); dy1 = abs(dy);
	px = 2 * dy1 - dx1;	py = 2 * dx1 - dy1;

	if (dy1 <= dx1)
	{
		if (dx >= 0) { x = x1; y = y1; xe = x2; }
		else { x = x2; y = y2; xe = x1; }
		count++;

		for (i = 0; x < xe; i++) {
			x = x + 1;
			if (px < 0) px = px + 2 * dy1;
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) y = y + 1; else y = y - 1;
				px = px + 2 * (dy1 - dx1);
			}
			count++;
		}
	}
	else
	{
		if (dy >= 0) { x = x1; y = y1; ye = y2; }
		else { x = x2; y = y2; ye = y1; }

		count++;

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
			count++;
		}
	}

	return count;
}

// Object set section ********************************************

// Used to set the object coordinates
void Object::SetPosition(float xPos, float yPos)
{
	this->xPos = xPos;
	this->yPos = yPos;
}

// Used to set object directions
void Object::SetDirection(int roation, bool flip)
{
	this->roation = roation;
	this->flip = flip;
}