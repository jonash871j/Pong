#include "Ball.h"
#include "Input.h"
#include "Sound.h"

float RandDireFloat()
{
	int a = rand() % 2;
	if (a == 0) return -static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	if (a == 1) return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

int DireInt(int a)
{
	if (a == 0) return -1;
	if (a == 1) return 1;
}

Ball::Ball(std::string spritePath, float mSpeed)
{
	Sprite sprite = { 1, 2, 2 };
	sprite.ImportLayer(spritePath, 0);
	this->sprite = sprite;
	this->mSpeed = mSpeed;
	xPos = float(XMID - 1);
	yPos = float(YMID + 5);
}

void Ball::SetDirection(float hDire, float vDire)
{
	this->hDire = hDire;
	this->vDire = vDire;
}

void Ball::SetMovement()
{
	if (newDirection == true)
	{
		SetDirection(DireInt(ballDirection), RandDireFloat());
		newDirection = false;
		mSpeedAdd += speedUpRate;
	}

	if (newWallDirection == true)
	{
		SetDirection(DireInt(ballDirection), -vDire);
		newWallDirection = false;
		mSpeedAdd += speedUpRate;
	}

	hsp = hDire * (mSpeed + mSpeedAdd);
	vsp = vDire * (mSpeed + mSpeedAdd);
}

void Ball::SetReset()
{
	auto Reset = [=]()
	{
		Sound::Play("./Sound/sndScore");
		xPos = float(XMID - 1);
		yPos = float(YMID + 5);
		mSpeedAdd = 0;
		newDirection = true;
		return 1;
	};

	if (xPos <= -16)
		ballPoint1 += Reset();
	if (xPos >= SCREENWIDTH + 16) {
		ballPoint2 += Reset();
	}
}

void Ball::SetCollision(Scene scene, Object player1, Object player2)
{
	// Collision code
	auto CollidingObject = [&](Object player, float hDire, float vDire)
	{
		if (ObjectCollide(player, hDire, vDire)) {
			while (!ObjectCollide(player, hDire, vDire)) {
				this->yPos += vDire;
				this->xPos += hDire;
			}
			if (vDire == 0) {
				Sound::Play("./Sound/sndPlatform");
				this->hsp = 0;
				ballDirection = SwitchBool(ballDirection);
			}
			else {
				Sound::Play("./Sound/sndMiss");
				this->vsp = 0;
			}
			newDirection = true;
		}
	};
	auto CollidingTile = [&](float hDire, float vDire)
	{
		for (int i = 0; i < sizeof(collisionArray); i++) {
			if (TilePreciseCollide(scene, hDire, vDire, 0, 0, collisionArray[i])) {
				while (!TilePreciseCollide(scene, hDire, vDire, 0, 0, collisionArray[i])) {
					xPos += hDire;
					yPos += vDire;
				}
				if (vDire == 0) this->hsp = 0;
				else{
					Sound::Play("./Sound/sndWall");
					this->vsp = 0;
				}
				newWallDirection = true;
			}
		}
	};

	// Collision at x axis
	CollidingObject(player1, hDire, 0);
	CollidingObject(player2, hDire, 0);
	CollidingTile(hDire, 0);
	xPos += hsp;

	// Collision at y axis
	CollidingObject(player1, 0, vDire);
	CollidingObject(player2, 0, vDire);
	CollidingTile(0, vDire);
	yPos += vsp;
}

void Ball::SetBallLogic(float speedUpRate)
{
	this->speedUpRate = speedUpRate;
	SetMovement();
	SetReset();
	
	if ((ballPoint1 >= 11) || (ballPoint2 >= 11))
	{ ballPoint1 = 0; ballPoint2 = 0; }
}

void Ball::Reset()
{
	this->mSpeedAdd = 0;
	xPos = float(XMID - 1);
	yPos = float(YMID + 5);
	ballPoint1 = 0;
	ballPoint2 = 0;
}