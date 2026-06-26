#include "conveyor.h"

Conveyor::Conveyor(int _worldX, int _worldY) : Machine(worldX, worldY) {
	worldX = _worldX;
	worldY = _worldY;
};

void Conveyor::draw(SDL_Renderer* renderer, float _x, float _y) {
	frameTimer++;
	if (frameTimer >= 32) {
		frameTimer = frameTimer % 32;
		frame++;
		frame = frame % 4;
	}

	SDL_FRect tileRect = { _x, _y, TILE_SIZE, TILE_SIZE };
	SDL_FRect texRect = { SPRITE_SIZE * 2 + frame * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE };
	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);

}


void Conveyor::DrawPreview(SDL_Renderer* renderer, float _x, float _y) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);

	SDL_FRect tileRect = { _x, _y, TILE_SIZE, TILE_SIZE };
	SDL_FRect texRect = { SPRITE_SIZE * 2, 0, SPRITE_SIZE, SPRITE_SIZE };

	SDL_SetTextureAlphaMod(textureList[TEX_TILES1], 128);
	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);
	SDL_SetTextureAlphaMod(textureList[TEX_TILES1], 255);
}