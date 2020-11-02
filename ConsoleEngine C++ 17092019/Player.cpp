#include "Player.h"
#include "Input.h"
#include "Sound.h"

float RandFloat(float min, float max)
{
	float a = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	if (a > max) a = max;
	if (a < min) a = min;
	return a;
}

int RandDireInt()
{
	int a = rand() % 2;
	if (a == 0) return -1;
	if (a == 1) return 1;
}

Player::Player(std::string spritePath, float mSpeed, float xPos, float yPos)
{
	Sprite sprite = { 1, 2, 8 };
	sprite.ImportLayer(spritePath, 0);
	this->sprite = sprite;
	this->mSpeed = mSpeed;
	aiSpeed = mSpeed;
	this->xPos = xPos;
	this->yPos = yPos;
	yStart = yPos;
}

void Player::SetInput(int keyDown, int keyUp)
{
	vDire = Input::KeyState(keyDown) - Input::KeyState(keyUp);
	vsp = vDire * mSpeed;
}

void Player::SetAi(Object ball, float viewArea)
{
	if (ObjectDistance(ball) < viewArea)
	{
		if (yPos < ball.GetYPos() - (sprite.GetHeight() / 2)) vDire = 1;
		if (yPos > ball.GetYPos() - (sprite.GetHeight() / 2)) vDire = -1;
		aiSpeed = RandFloat(0.1f, mSpeed);
	}
	else if (vsp == 0)
	{
		vDire = RandDireInt();
		aiSpeed = RandFloat(0.1f, mSpeed);
	}

	vsp = vDire * aiSpeed;
}

void Player::SetCollision(Scene scene, Object ball)
{
	if (ObjectCollide(ball, 0, vsp)) {
		while (!ObjectCollide(ball, 0, vDire))
			yPos += vDire;
		vsp = 0;
	}

	for (int i = 0; i < sizeof(collisionArray); i++) {
		if (TilePreciseCollide(scene, 0, vsp, 0, 0, collisionArray[i])) {
			while (!TilePreciseCollide(scene, 0, vDire, 0, 0, collisionArray[i]))
				yPos += vDire;
			vsp = 0;
		}
	}
	yPos += vsp;
}

void Player::Reset()
{
	yPos = yStart;
}