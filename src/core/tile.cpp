#include "tile.h"

Tile::Tile(int _x, int _y) {
	x = _x;
	y = _y;
}

void Tile::draw(SDL_Renderer* renderer, float _x, float _y) {
	int tileX = x % 2;
	int tileY = y % 2;
	SDL_FRect tileRect = { _x + x * TILE_SIZE, _y + y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
	SDL_FRect texRect = {tileX * SPRITE_SIZE, tileY * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE };
	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);
	//SDL_SetRenderDrawColor(renderer, 64 + x * 4, 64 + y * 4, 0, SDL_ALPHA_OPAQUE);
	//SDL_RenderRect(renderer, &tileRect);
}

