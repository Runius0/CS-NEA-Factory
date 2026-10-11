#pragma once
#include "../../core.h"

const int TILE_SIZE = 32;

enum tileFlags {
	T_SOLID = 1,
	T_REPLACEABLE = 2,
	T_INTERACTABLE = 4,
	T_USESITEMS = 8,
	T_ISORE = 16
};

class World;

class Tile {
public:
	int worldX;
	int worldY;
	int itemID = 0; // ID of the item which placed the obect, 0 means it was not placed
	unsigned int flags = T_REPLACEABLE;
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