#pragma once
#include "Object.h"

class Player : Object
{
private:
	char collisionArray[2] = { 'U', 'D' };
	float mSpeed = 0, aiSpeed = 0;
	float vsp = 0;
	float vDire = 0;
	float yStart;

public:
	Player(std::string spritePath, float mSpeed, float xPos, float yPos);
	Player() {};

	void SetInput(int keyDown, int keyUp);
	void SetAi(Object ball, float viewArea);
	void SetCollision(Scene scene, Object ball);
	void Reset();

	Object GetObject readonly* this rs
};

