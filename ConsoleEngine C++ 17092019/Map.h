#pragma once

static Scene map = { 11, 9, 8, 8, 8, 8 };

static void GenerateMap()
{
	std::string spritePath = "./Sprite/";
	Sprite sprUpperLine = { 1, 8, 8 };
	Sprite sprDownLine = { 1, 8, 8 };
	Sprite sprMiddleLine = { 1, 8, 8 };

	sprUpperLine.ImportLayer(spritePath + "spr_pongLineUp", 0);
	sprDownLine.ImportLayer(spritePath + "spr_pongLineDown", 0);
	sprMiddleLine.ImportLayer(spritePath + "spr_pongLine", 0);
	map.ImportMap("map");
	map.SetSpriteID('U', sprUpperLine);
	map.SetSpriteID('D', sprDownLine);
	map.SetSpriteID('M', sprMiddleLine);
	map.UpdatePixelArray();
}