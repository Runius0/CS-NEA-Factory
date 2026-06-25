#pragma once
#include "../../core.h"

const int TILE_SIZE = 32;
const int SPRITE_SIZE = 16;


class Tile {
public:
	int x;
	int y;
	int worldX;
	int worldY;
	Tile(int x, int y, int worldX, int worldY);
	Tile();
	virtual void draw(SDL_Renderer* renderer, float x, float y);
};

class Grass : public Tile {
	public:
		Grass(int x, int y, int worldX, int worldY);
		void draw(SDL_Renderer* renderer, float x, float y) override;

};