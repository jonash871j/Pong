#pragma once
#include "Object.h"

class Ball : Object
{
private:
	char collisionArray[2] = { 'U', 'D' };
	bool newDirection = true;
	bool newWallDirection = false;
	bool ballDirection = false;
	int ballPoint1 = 0, ballPoint2 = 0;
	float mSpeed = 0, mSpeedAdd = 0;
	float speedUpRate;
	float vsp = 0, hsp = 0;
	float vDire = 0, hDire = 0;


private:
	void SetDirection(float hDire, float vDire);
	void SetMovement();
	void SetReset();

public:
	Ball(std::string spritePath, float mSpeed);
	Ball() {};
	void SetCollision(Scene scene, Object player1, Object player2);
	void SetBallLogic(float speedUpRate);
	void Reset();

public:
	Object GetObject readonly *this rs
	int GetPoint1 readonly ballPoint1 rs
	int GetPoint2 readonly ballPoint2 rs
};