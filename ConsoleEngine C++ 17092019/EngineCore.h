#pragma once
#include <string>
#include <vector>
#include "VirtualKeyDefines.h"
#define BLACK 0
#define D_BLUE 1
#define D_GREEN 2
#define D_CYAN 3
#define D_RED 4
#define PURPLE 5
#define D_YELLOW 6
#define L_GREY 7
#define D_GREY 8
#define BLUE 9
#define GREEN 10
#define CYAN 11
#define RED 12
#define MAGENTA 13
#define YELLOW 14
#define WHITE 15
#define readonly () const { return
#define readonly_1D (int x) const { return
#define readonly_2D (int x, int y) const { return
#define readonly_3D (int x, int y, int z) const { return
#define rs ;}

static enum Character
{
	cFULL = 219,
	CNULL = 0,
};

static enum TextDirection
{
	tLEFTRIGHT = 0,
	tRIGHTLEFT = 1,
	tTOPBUTTOM = 2,
	tBUTTOMTOP = 3,
};

static std::vector<int> IntegerToArray(int x)
{
	std::vector <int> resultArray;
	while (true)
	{
		resultArray.insert(resultArray.begin(), x % 10);
		x /= 10;
		if (x == 0)
			return resultArray;
	}
}

// Returns only 1, 0 or -1
static int Sign(float n)
{
	if (n > 0) n = 1;
	if (n < 0) n = -1;
	return int(n);
}

// Returns color value
static char C(char foreground, char background)
{
	return foreground + (16 * background);
}

// Toggles bool
static bool SwitchBool(bool a)
{
	switch (a){
	case true: a = false; return a;
	case false: a = true; return a;
	}
}