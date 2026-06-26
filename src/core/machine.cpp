#include "machine.h"

Machine::Machine(int _worldX, int _worldY) {
	worldX = _worldX;
	worldY = _worldY;
}


bool Machine::canPlace(World* world, int worldX, int worldY, int width, int height) {
	for (int i = worldX; i < worldX + width; i++) {
		for (int j = worldY; j < worldY + height; j++) {
			if (world->getTile(i, j)->solid) {
				return false;
			}
		}
	}
	return true;
}

void Machine::place(World* world) {
	for (int i = worldX; i < worldX + width; i++) {
		for (int j = worldY; j < worldY + height; j++) {
			world->setTile(this, i, j);
		}
	}
}

void Machine::clear(World* world) {
	for (int i = worldX; i < worldX + width; i++) {
		for (int j = worldY; j < worldY + height; j++) {
			world->setTile(new Grass(i, j), i, j);
		}
	}
}

void Machine::DrawPreview(SDL_Renderer* renderer, float _x, float _y) {
	SDL_SetRenderDrawColor(renderer ,255,255, 255, 128);

	SDL_FRect tileRect = { _x, _y, TILE_SIZE, TILE_SIZE };
	SDL_FRect texRect = { 0, 0, SPRITE_SIZE, SPRITE_SIZE };


	SDL_SetTextureAlphaMod(textureList[TEX_TILES1], 128);
	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);
	SDL_SetTextureAlphaMod(textureList[TEX_TILES1], 255);
}