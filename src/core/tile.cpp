#include "tile.h"

Tile::Tile(int _worldX, int _worldY) {
	worldX = _worldX;
	worldY = _worldY;
}
Tile::Tile() {
	worldX = 0;
	worldY = 0;
}

void Tile::tick(int gameTick) {
	return;
}

void Tile::draw(SDL_Renderer* renderer, float _x, float _y) {
	SDL_FRect tileRect = { _x, _y, TILE_SIZE, TILE_SIZE };
	SDL_SetRenderDrawColor(renderer, 64 + (worldX % 32) * 4, 64 + (worldY % 32) * 4, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderRect(renderer, &tileRect);
}

Grass::Grass(int _worldX, int _worldY) {
	worldX = _worldX;
	worldY = _worldY;
}

void Grass::draw(SDL_Renderer* renderer, float _x, float _y) {
	int tileX = worldX % 2;
	int tileY = worldY % 2;
	SDL_FRect tileRect = { _x, _y, TILE_SIZE, TILE_SIZE };
	SDL_FRect texRect = { tileX * SPRITE_SIZE, tileY * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE };
	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);

}