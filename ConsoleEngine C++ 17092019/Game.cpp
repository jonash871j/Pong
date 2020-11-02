#include "Game.h"
#include <thread>
#define PLAYER_MID float(YMID + 2)
#define YOFF -6

void Game::Setup()
{
	// Creating game objects
	std::string spritePath = "./Sprite/";
	Player player1(spritePath + "spr_pongPlatform", 0.5f, 6.0f, PLAYER_MID);
	Player player2(spritePath + "spr_pongPlatform", 0.5f, float(SCREENWIDTH - 8), PLAYER_MID);
	Ball ball1(spritePath + "spr_pongBall", 0.18f);
	this->player1 = player1;
	this->player2 = player2;
	this->ball1 = ball1;

	// Generates map
	GenerateMap();
}

void Game::Drawing()
{
	Draw::Map(map, 0, YOFF);
	Draw::SpritePlain(player1.GetObject(), 0, YOFF);
	Draw::SpritePlain(player2.GetObject(), 0, YOFF);
	Draw::SpritePlain(ball1.GetObject(), 0, YOFF);
	Draw::Text(fntPong, 26, 9 + YOFF, ball1.GetPoint2(), 0, WHITE);
	Draw::Text(fntPong, 54, 9 + YOFF, ball1.GetPoint1(), 0, WHITE);
}

void Game::Begin(bool ai, float difficulty, float speedUpRate)
{
	while (!Input::KeyPressed(VK_ESCAPE))
	{
		// Ball
		ball1.SetBallLogic(speedUpRate);
		ball1.SetCollision(map, player1.GetObject(), player2.GetObject());

		// Players
		if (ai == true) player1.SetAi(ball1.GetObject(), difficulty);
		else			player1.SetInput('S', 'W');

		player1.SetCollision(map, ball1.GetObject());

		player2.SetInput(VK_DOWN, VK_UP);
		player2.SetCollision(map, ball1.GetObject());

		// Drawing
		Draw::Background(219, BLACK);
		Drawing();

		// Update
		Console::Update();
		std::this_thread::sleep_for(std::chrono::nanoseconds(200));
		//Delay(1);
	}
}


void Game::Demo()
{
	// Ball
	ball1.SetBallLogic(0.005f);
	ball1.SetCollision(map, player1.GetObject(), player2.GetObject());

	// Players
	player1.SetAi(ball1.GetObject(), 32.5f);
	player1.SetCollision(map, ball1.GetObject());
	player2.SetAi(ball1.GetObject(), 32.5f);
	player2.SetCollision(map, ball1.GetObject());

	// Drawing
	Drawing();
}

void Game::Reset()
{
	player1.Reset();
	player2.Reset();
	ball1.Reset();
}
