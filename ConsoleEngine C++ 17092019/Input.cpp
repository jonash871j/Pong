#include "Input.h"
#include <wtypes.h>

#define NOT_PRESSED 0
#define IS_PRESSED 1
#define FIRST_PRESS 2
#define IS_RELEASED 3

#pragma region PRIVATE
byte keyStateMap[255] = { NOT_PRESSED };
#pragma endregion

#pragma region PUBLIC

// Returns true if ketstate is true
bool Input::KeyState(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
		return true;
	else return false;
}

// Input key hold delayed loop
bool Input::KeyStateDelayedLoop(int key)
{
	if (GetAsyncKeyState(key) & 0x0001)
		return true;
	else return false;
}

// Returns true if key is pressed
bool Input::KeyPressed(int key)
{
	if ((GetAsyncKeyState(key) & 0x8000) && (keyStateMap[key] == NOT_PRESSED))
		keyStateMap[key] = FIRST_PRESS;

	if (keyStateMap[key] == FIRST_PRESS)
	{
		keyStateMap[key] = IS_PRESSED;
		return true;
	}
	if (GetAsyncKeyState(key) == false)
		keyStateMap[key] = NOT_PRESSED;
	return false;
}

// Returns true if key is released
bool Input::KeyReleased(int key)
{
	if ((GetAsyncKeyState(key) & 0x8000) && (keyStateMap[key] == NOT_PRESSED))
		keyStateMap[key] = IS_PRESSED;

	if ((GetAsyncKeyState(key) == false) && (keyStateMap[key] == IS_PRESSED))
		keyStateMap[key] = IS_RELEASED;


	if (keyStateMap[key] == IS_RELEASED)
	{
		keyStateMap[key] = NOT_PRESSED;
		return true;
	}
	return false;
}

// Used to clear all keystates
void Input::ClearKeyBuffer()
{
	for (int i = 0; i < 0xFF; i++)
		if (keyStateMap[i] == NOT_PRESSED);
}
#pragma endregion