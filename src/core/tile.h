#pragma once
#include "../../core.h"

const int TILE_SIZE = 32;

class World;

class Tile {
public:
	int worldX;
	int worldY;
	bool solid = false;
	Tile(int worldX, int worldY);
	Tile();
	virtual void tick(World* world, int gameTick);
	virtual void draw(SDL_Renderer* renderer, float x, float y);
	virtual void drawOverlay(SDL_Renderer* renderer, float x, float y) {};
};

class Grass : public Tile {
	public:
		Grass(int worldX, int worldY);
		void draw(SDL_Renderer* renderer, float x, float y) override;

};