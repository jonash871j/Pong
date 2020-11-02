#pragma once
#include "Input.h"
#include "Draw.h"
#include "Player.h"
#include "Ball.h"
#include "Map.h"

class Game
{
private:
	Font fntPong = { "./Font/FontPong/", 8, 8 };
	Player player1;
	Player player2;
	Ball ball1;
private:
	void Drawing();

public:
	Game() {};
	void Setup();
	void Begin(bool ai, float difficuly, float speedUpRate);
	void Demo();
	void Reset();
};