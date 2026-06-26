#pragma once
#include "../../core.h"

const int TILE_SIZE = 32;
const int SPRITE_SIZE = 16;


class Tile {
public:
	int worldX;
	int worldY;
	const bool solid = false;
	Tile(int worldX, int worldY);
	Tile();
	virtual void draw(SDL_Renderer* renderer, float x, float y);
};

class Grass : public Tile {
	public:
		const bool solid = false;
		Grass(int worldX, int worldY);
		void draw(SDL_Renderer* renderer, float x, float y) override;

};