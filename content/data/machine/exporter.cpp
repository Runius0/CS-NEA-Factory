#include "exporter.h"

Exporter::Exporter(int _worldX, int _worldY, Direction direction) : Machine(_worldX, _worldY, direction) {
	width = 1;
	height = 1;
};

void Exporter::draw(SDL_Renderer* renderer, float _x, float _y) {

	SDL_FRect tileRect = { _x, _y, TILE_SIZE, TILE_SIZE };
	SDL_FRect texRect = { SPRITE_SIZE * 4 + frame * SPRITE_SIZE, SPRITE_SIZE * 4 + SPRITE_SIZE * direction, SPRITE_SIZE, SPRITE_SIZE };
	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);

}

void Exporter::tick(int gameTick) {
	frame = gameTick % 4;
}


void Exporter::DrawPreview(SDL_Renderer* renderer, float _x, float _y, Direction _direction) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);

	SDL_FRect tileRect = { _x, _y, TILE_SIZE, TILE_SIZE };
	SDL_FRect texRect = { SPRITE_SIZE * 4, SPRITE_SIZE * 4 + SPRITE_SIZE * _direction, SPRITE_SIZE, SPRITE_SIZE };

	SDL_SetTextureAlphaMod(textureList[TEX_TILES1], 128);
	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);
	SDL_SetTextureAlphaMod(textureList[TEX_TILES1], 255);
}