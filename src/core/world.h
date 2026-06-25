#pragma once

#include "../../core.h"
#include "chunk.h"



class World {
	Chunk* chunkMap[11][11];

	// coordinates of top left chunk
	int x;
	int y;
public:
	// functions
	World();

	void addChunk(int x, int y);
	Tile* getTile(int x, int y);
	//bool isSpaceOccupied(int _x, int _y, int width, int height);
	void draw(SDL_Renderer* renderer, float x, float y);
	void tick();
};