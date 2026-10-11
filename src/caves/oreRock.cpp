#include "oreRock.h"


OreRock::OreRock(int worldX, int worldY, SDL_FRect _spriteBase, Item* _type) : Tile(worldX, worldY) {
	spriteBase = _spriteBase;
	type = _type;
	variant = SDL_rand(3);
	flags |= T_ISORE | T_SOLID;
	flags ^= T_REPLACEABLE;
};

void OreRock::draw(SDL_Renderer* renderer, float _x, float _y) {

	SDL_FRect tileRect = { _x, _y, TILE_SIZE, TILE_SIZE };
	SDL_FRect texRect = {spriteBase.x + variant * SPRITE_SIZE, spriteBase.y, spriteBase.w, spriteBase.h};
	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);

}