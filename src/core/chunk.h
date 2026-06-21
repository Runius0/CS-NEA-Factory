#pragma once
#include "../../SDL_Include.h"
#include <array>

const int CHUNK_SIZE = 32;
const int TILE_SIZE = 32;
const int CHUNK_SIZE_PX = TILE_SIZE * CHUNK_SIZE;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

class Chunk {
	int x;
	int y;
public:
	Chunk(int x, int y);
	void draw(SDL_Renderer* renderer, float x, float y);
};