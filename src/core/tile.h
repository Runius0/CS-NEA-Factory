#pragma once
#include "../../core.h"

const int TILE_SIZE = 32;
const int SPRITE_SIZE = 16;


class Tile {
	int x;
	int y;
public:
	Tile(int x, int y);
	virtual void draw(SDL_Renderer* renderer, float x, float y);
};

class Grass : public Tile {
	void draw(SDL_Renderer* renderer, float x, float y) override;

};