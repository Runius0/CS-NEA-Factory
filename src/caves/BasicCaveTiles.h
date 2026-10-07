#pragma once
#include "../core/world.h"

class CaveDirt : public Tile {
public:
	CaveDirt(int worldX, int worldY);
	void draw(SDL_Renderer* renderer, float x, float y) override;
};

class CaveWall : public Tile {
	bool initialized = false;
	int floorDist = 0;
public:
	CaveWall(int worldX, int worldY);
	void draw(SDL_Renderer* renderer, float x, float y) override;
	void tick(World* world, int gameTick) override;

};