#include "machine.h"

Machine* MACHINE[256];

Machine::Machine() {
	solid = true;
	replaceable = false;
}

void Machine::init(int _worldX, int _worldY, Direction _direction) {
	direction = _direction;
	worldX = _worldX;
	worldY = _worldY;
};

Machine* Machine::copy(int _worldX, int _worldY, Direction _direction) {
	Machine* out = new Machine();
	out->init(_worldX, _worldY, _direction);
	out->ID = ID;
	return out;
};

bool Machine::canPlace(World* world, int worldX, int worldY, Direction direction) {
	// if rotated, then check rotated
	if (direction % 2 == 1) {
		for (int i = worldX; i < worldX + height; i++) {
			for (int j = worldY; j < worldY + width; j++) {
				if (!world->getTile(i, j)) {
					return false;
				}
				if (!world->getTile(i, j)->replaceable) {
					return false;
				}
			}
		}
		return true;

	}

	for (int i = worldX; i < worldX + width; i++) {
		for (int j = worldY; j < worldY + height; j++) {
			if (!world->getTile(i, j)) {
				return false;
			}
			if (!world->getTile(i, j)->replaceable) {
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

void Machine::DrawPreview(SDL_Renderer* renderer, float _x, float _y, Direction direction) {
	SDL_SetRenderDrawColor(renderer ,255,255, 255, 128);

	SDL_FRect tileRect = { _x, _y, TILE_SIZE, TILE_SIZE };
	SDL_FRect texRect = { 0, 0, SPRITE_SIZE, SPRITE_SIZE };


	SDL_SetTextureAlphaMod(textureList[TEX_TILES1], 128);
	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);
	SDL_SetTextureAlphaMod(textureList[TEX_TILES1], 255);
}