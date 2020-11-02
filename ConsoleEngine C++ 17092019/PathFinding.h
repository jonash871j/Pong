#pragma once
#include "Scene.h"

class PathFinding
{
private:
	// Path defintions
	enum pathDef
	{
		SOLID = 65536,
		START = 65535,
		END = 65534,
		NEW_CHUNK = 65533,
		NEW_CHUNK_IN_QUEUE = 65532
	};

	//Coordinate memory
	std::vector<int> xMemory;
	std::vector<int> yMemory;
	std::vector<int> xNewMemory;
	std::vector<int> yNewMemory;

	// Pathfinding
	Scene scene;
	int mWidth, mHeight;
	char** mapArray;
	unsigned short** pathArray;


	// Other
	void CleanUp();

	// Path wave propagation 
	unsigned short currentDistance;
	unsigned short lowestValue;
	unsigned short currentValue;
	void GenerateNewChunk(int xCurrent, int yCurrent);
	void SetNewChunk(int x, int y);
	bool CheckLowestValue(int x, int y);

	// Path randomize
	int lastDirection = 4;

public:

	PathFinding(Scene scene, std::vector<char> solidArray);
	PathFinding() {};

	// "Deconstructer" \n Does also delete pointer arrays
	~PathFinding();

	// Used to generate path
	bool Generate(int xStart, int yStart, int xEnd, int yEnd);

	bool GenerateRand(int xStart, int yStart);

	// Pathfinding get section **************************************
	int GetPathArray readonly_2D pathArray[y][x] rs
	int GetMapArray readonly_2D mapArray[y][x] rs
	int GetPathWidth readonly mWidth rs
	int GethPathHeight readonly mHeight rs
};

