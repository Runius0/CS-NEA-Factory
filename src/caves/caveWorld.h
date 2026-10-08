#pragma once
#include "../core/world.h"
#include "BasicCaveTiles.h"

class CaveWorld : public World {
public:
	CaveWorld();
	void addChunk(int x, int y);
	void setTile(Tile* tile, int _x, int _y);
};
class CaveChunk : public Chunk {
public:
	CaveChunk(int x, int y);

};