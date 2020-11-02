#pragma once
#include "Console.h"

namespace Input
{
	// Returns true if ketstate is true
	bool KeyState(int key);

	bool KeyStateDelayedLoop(int key);

	// Returns true if key is pressed
	bool KeyPressed(int key);

	// Returns true if key is released
	bool KeyReleased(int key);

	// Used to clear all keystates
	void ClearKeyBuffer();
}
