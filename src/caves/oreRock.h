#pragma once
#include "../core/world.h"
#include "../core/item.h"

class OreRock : public Tile {
	int variant;
	SDL_FRect spriteBase;
public:
	Item* type;
	OreRock(int worldX, int worldY, SDL_FRect spriteBase, Item* type);
	void draw(SDL_Renderer* renderer, float x, float y) override;
};
