#pragma once
#include "Scene.h"

class Object
{
protected:
	float xPos, yPos;
	int roation = 0;
	bool flip = 0;

public:
	Sprite sprite = { 0, 0, 0 };

	Object(int spriteAmount, int width, int height);
	Object(Sprite sprite);
	Object() {};
	~Object();

	// Object events *************************************************

	// Returns true if this object collides with another object
	bool ObjectCollide(Object object, float xOff, float yOff);

	// Returns true if this object collides with a tile from a scene
	bool TileCollide(Scene scene, char tile);

	// Returns true if this object collides with a character of tile from a scene
	bool TilePreciseCollide(Scene scene, float xOff, float yOff, int xSizeOff, int ySizeOff, int tile);

	// Used to get distance to another object
	float ObjectDistance(Object object);


	// Object set section ********************************************

	// Used to set the object coordinates
	void SetPosition(float xPos, float yPos);

	// Used to set object directions
	void SetDirection(int roation, bool flip);

	// Object get section ********************************************

	float GetXPos readonly xPos rs
	float GetYPos readonly yPos rs
	bool GetFlip readonly flip rs
	int GetRoation readonly roation rs
};