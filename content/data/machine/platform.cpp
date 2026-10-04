#include "platform.h"

SurfacePlatform::SurfacePlatform() : Machine() {
	width = 4;
	height = 4;
};

void SurfacePlatform::init(int _worldX, int _worldY, Direction direction) {
	Machine::init(_worldX, _worldY, direction);
};

Machine* SurfacePlatform::copy(int _worldX, int _worldY, Direction _direction) {
	Machine* out = new SurfacePlatform();
	out->init(_worldX, _worldY, _direction);
	out->ID = ID;
	return out;
};

bool SurfacePlatform::interract(Player* player) {
	player->setAnimation(descend);
	return false;
}

void SurfacePlatform::draw(SDL_Renderer* renderer, float _x, float _y) {

	SDL_FRect tileRect = { _x, _y, TILE_SIZE * 4, TILE_SIZE * 4 };
	SDL_FRect texRect = { SPRITE_SIZE * 8, SPRITE_SIZE * 5, SPRITE_SIZE * 4, SPRITE_SIZE * 4 };
	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);

}

void SurfacePlatform::DrawPreview(SDL_Renderer* renderer, float _x, float _y, Direction _direction) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);

	SDL_FRect tileRect = { _x, _y, TILE_SIZE*4, TILE_SIZE*4 };
	SDL_FRect texRect = { SPRITE_SIZE * 8, SPRITE_SIZE * 5, SPRITE_SIZE * 4, SPRITE_SIZE * 4 };

	SDL_SetTextureAlphaMod(textureList[TEX_TILES1], 128);
	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);
	SDL_SetTextureAlphaMod(textureList[TEX_TILES1], 255);
}
