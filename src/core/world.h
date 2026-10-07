#pragma once

#include "../../core.h"
#include "chunk.h"



class World {

protected:
	// coordinates of top left chunk
	int x;
	int y;
	Chunk* chunkMap[11][11];
public:
	// functions
	World();

	virtual void addChunk(int x, int y);
	Tile* getTile(int x, int y);
	Tile* getTile(float x, float y);
	void setTile(Tile* tile, int x, int y);
	//bool isSpaceOccupied(int _x, int _y, int width, int height);
	void draw(SDL_Renderer* renderer, float x, float y);
	void snapToGrid(float* x, float* y);
	void tick(int gameTick);
};