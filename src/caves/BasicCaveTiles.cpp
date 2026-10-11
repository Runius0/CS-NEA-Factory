#include "BasicCaveTiles.h"

CaveDirt::CaveDirt(int _worldX, int _worldY) {
	worldX = _worldX;
	worldY = _worldY;
}

void CaveDirt::draw(SDL_Renderer* renderer, float _x, float _y) {
	int tileX = SDL_abs(worldX) % 2 + 8;
	int tileY = SDL_abs(worldY) % 2 + 2;
	SDL_FRect tileRect = { _x, _y, TILE_SIZE, TILE_SIZE };
	SDL_FRect texRect = { tileX * SPRITE_SIZE, tileY * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE };
	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);

}

CaveWall::CaveWall(int _worldX, int _worldY) {
	worldX = _worldX;
	worldY = _worldY;
	flags |= T_SOLID;
	flags ^= T_REPLACEABLE;
}

void CaveWall::tick(World* world, int gameTick) {
	if (initialized) {
		return;
	}
	if (world->getTile(worldX, worldY + 1) && !(world->getTile(worldX, worldY + 1)->flags & T_SOLID)) {
		floorDist = 1;
	}
	else if (world->getTile(worldX, worldY + 2) && !(world->getTile(worldX, worldY + 2)->flags & T_SOLID)) {
		floorDist = 2;
	}
}

void CaveWall::draw(SDL_Renderer* renderer, float _x, float _y) {
	SDL_FRect tileRect = { _x, _y, TILE_SIZE, TILE_SIZE };
	SDL_FRect texRect = { 10 * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE };
	if (floorDist != 0) {
		texRect = { 8 * SPRITE_SIZE, (float)floorDist * -SPRITE_SIZE + 2 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE };
	}
	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);

}