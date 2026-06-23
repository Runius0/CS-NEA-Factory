#pragma once
#include "../../core.h"
#include "tile.h"
#include <array>

const int CHUNK_SIZE = 32;
const int CHUNK_SIZE_PX = TILE_SIZE * CHUNK_SIZE;
class Chunk {
	Tile* tileMap[CHUNK_SIZE][CHUNK_SIZE];

	int x;
	int y;
public:
	Chunk(int x, int y);
	void draw(SDL_Renderer* renderer, float x, float y);
};