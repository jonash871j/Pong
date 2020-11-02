#include "Engine.h"
#include "Game.h"
#include "Menu.h"

#define MAIN_MENU 0
#define OPTION_MENU 1
#define GAME_MENU 2
#define DIFFICULTY_MENU 3

Game game;
Sprite logo(1, 32, 12);
Sprite splash(1, 64, 32);

int cMenu = MAIN_MENU;
std::vector<std::string> mainMenu = { "Play", "Options", "Quit" };
std::vector<std::string> optionMenu = { "Window", "Sound", "Back" };
std::vector<std::string> gameMenu = { "1 VS ai", "1 VS 1", "Back" };
std::vector<std::string> difficultyMenu = { "Easy", "Medium", "Hard", "Insane", "Back" };
Menu mMain(mainMenu);
Menu mOption(optionMenu);
Menu mGame(gameMenu);
Menu mDifficulty(difficultyMenu);

bool exitGame = false;
bool soundState = true;
int windowStyle = 1;

void ConsoleSetup()
{
	Console::Create(88, 60);
	//Console::SetFont(L"Lucida Console", 12, 12);
	Console::SetFont(L"Terminal", 16, 16);
	srand(time(NULL));

	// Set Console Color
	ColorPalette cpDefault;
	cpDefault.ImportColorPalette("./Color/Default");
	Console::SetColorPalette(cpDefault);

	// Import logo
	logo.ImportLayer("./Sprite/spr_pongLogo", 0);
	splash.ImportLayer("./Sprite/spr_consoleSplashScreen", 0);
}

void MainMenuEvent()
{
	switch (mMain.GetClickedPosition())
	{
	case 0:
		cMenu = GAME_MENU;
		break;
	case 1:
		cMenu = OPTION_MENU;
		break;
	case 2: 
		exitGame = true;
		break;
	default: break;
	}

}
void OptionMenuEvent()
{
	switch (mOption.GetClickedPosition())
	{
	case 0:
		windowStyle++;
		switch (windowStyle)
		{
		default:
			windowStyle = 0;
		case 0:
			Console::SetFont(L"Lucida Console", 21, 18);
			break;
		case 1: 
			Console::SetFont(L"Terminal", 16, 16); 
			break;
		case 2:
			Console::SetFont(L"Terminal", 12, 16);
			break;
		case 3:
			Console::SetFont(L"Lucida Console", 12, 12);
			break;
		case 4:
			Console::SetFont(L"Terminal", 8, 8);
			break;
		case 5:
			Console::SetFont(L"Terminal", 4, 6);
			break;
		case 6:
			Console::SetFont(L"Lucida Console", 4, 4);
			break;

		}
		break;
	case 1:
		soundState = SwitchBool(soundState);
		Sound::SwitchEnableSound(soundState);
		break;
	case 2:
		cMenu = MAIN_MENU;
		break;
	default: break;
	}
}
void GameMenuEvent()
{
	switch (mGame.GetClickedPosition())
	{
	case 0:
		cMenu = DIFFICULTY_MENU;
		break;
	case 1:
		game.Reset();
		game.Begin(false, 0, 0.005f);
		break;
	case 2:
		cMenu = MAIN_MENU;
		break;
	default: break;
	}
}
void DifficultyMenuEvent()
{
	switch (mDifficulty.GetClickedPosition())
	{
	case 0:
		game.Reset();
		game.Begin(true, 10.0f, 0.005f);
		break;
	case 1:
		game.Reset();
		game.Begin(true, 25.0f, 0.005f);
		break;
	case 2:
		game.Reset();
		game.Begin(true, 32.5f, 0.005f);
		break;
	case 3:
		game.Reset();
		game.Begin(true, 50.0f, 0.005f);
		break;
	case 4:
		cMenu = GAME_MENU;
		break;
	default: break;
	}
}

int main()
{
	// Setups console
	ConsoleSetup();
	game.Setup();
	
	// Splash Screen
	Draw::Background(219, BLACK);
	Draw::SpritePlain(splash, XMID - 27, YMID - 16);
	Console::WriteString(0, SCREENHEIGHT - 1, "v13.12.2019", 0, WHITE);
	Console::WriteString(SCREENWIDTH - 8, SCREENHEIGHT - 1, "BY JONAS", 0, WHITE);
	Console::Update();
	Delay(2500);

	while (!exitGame)
	{
		Draw::Background(219, BLACK); 
		Console::WriteString(0, SCREENHEIGHT - 3, "PONG, v1.1b", 0, WHITE);

		// Draw game demo
		game.Demo();

		// Draw menu
		Draw::SpritePlain(logo, XMID - 16, YMID - 16);
		switch (cMenu){
		case MAIN_MENU:
			mMain.Drawing();
			MainMenuEvent();
			break;
		case OPTION_MENU:
			mOption.Drawing();
			OptionMenuEvent();
			break;
		case GAME_MENU:
			mGame.Drawing();
			GameMenuEvent();
			break;
		case DIFFICULTY_MENU:
			mDifficulty.Drawing();
			DifficultyMenuEvent();
			break;
		default: break;
		}

		// Update
		Console::Update();
		Delay(1);
	}
	return 0;
}