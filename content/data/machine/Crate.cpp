#include "Crate.h"

Crate::Crate(int _worldX, int _worldY, Direction direction) : Machine(_worldX, _worldY, direction) {
	width = 1;
	height = 1;
	ID = 4;
};

void Crate::draw(SDL_Renderer* renderer, float _x, float _y) {

	SDL_FRect tileRect = { _x, _y, TILE_SIZE, TILE_SIZE };
	SDL_FRect texRect = { SPRITE_SIZE * 4, SPRITE_SIZE * 3, SPRITE_SIZE, SPRITE_SIZE };
	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);

}

ItemStack* Crate::extractItem() {
	return new ItemStack(ITEM[ID], 1);
}


void Crate::DrawPreview(SDL_Renderer* renderer, float _x, float _y, Direction _direction) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);

	SDL_FRect tileRect = { _x, _y, TILE_SIZE, TILE_SIZE };
	SDL_FRect texRect = { SPRITE_SIZE * 4, SPRITE_SIZE * 3, SPRITE_SIZE, SPRITE_SIZE };

	SDL_SetTextureAlphaMod(textureList[TEX_TILES1], 128);
	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);
	SDL_SetTextureAlphaMod(textureList[TEX_TILES1], 255);
}