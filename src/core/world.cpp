#include "world.h"

World::World() {
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			chunkMap[i][j] = nullptr;
		}
	}
	x = -5;
	y = -5;

};

void World::addChunk(int _x, int _y) {
	chunkMap[_x - x][_y - y] = new Chunk(_x, _y);
};

void World::draw(SDL_Renderer* renderer, float _x, float _y) {
	int chunkX = (int)(_x / CHUNK_SIZE_PX);
	int chunkY = (int)(_y / CHUNK_SIZE_PX);
	


	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if ((i - x + chunkX >= 0) && (i - x + chunkX < std::size(chunkMap)) && chunkMap[i - x + chunkX][j - y + chunkY]) {
				chunkMap[i - x + chunkX][j - y + chunkY]->draw(renderer, _x, _y);
			}
		}
	}
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if ((i - x + chunkX >= 0) && (i - x + chunkX < std::size(chunkMap)) && chunkMap[i - x + chunkX][j - y + chunkY]) {
				chunkMap[i - x + chunkX][j - y + chunkY]->drawOverlay(renderer, _x, _y);
			}
		}
	}
};

void World::tick(int gameTick) {
	for (int i = 0; i < std::size(chunkMap); i++) {
		for (int j = 0; j < std::size(chunkMap[i]); j++) {
			if (chunkMap[i][j]) {
				chunkMap[i][j]->tick(this, gameTick);
			}
		}
	}
};


Tile* World::getTile(int _x, int _y) {
	int chunkX = (int)floor((float)_x / CHUNK_SIZE);
	int chunkY = (int)floor((float)_y / CHUNK_SIZE);



	int tileX = _x >= 0 ? _x % CHUNK_SIZE : CHUNK_SIZE - ((-1 - _x) % CHUNK_SIZE) - 1;
	int tileY = _y >= 0 ? _y % CHUNK_SIZE : CHUNK_SIZE - ((-1 - _y) % CHUNK_SIZE) - 1;

	if (chunkMap[chunkX - x][chunkY - y] == NULL) {
		return NULL;
	}

	return chunkMap[chunkX - x][chunkY - y]->getTile(tileX, tileY);
}

void World::setTile(Tile* tile, int _x, int _y) {
	int chunkX = (int)floor((float)_x / CHUNK_SIZE);
	int chunkY = (int)floor((float)_y / CHUNK_SIZE);

	int tileX = _x >= 0 ? _x % CHUNK_SIZE : CHUNK_SIZE - ((-1 - _x) % CHUNK_SIZE) - 1;
	int tileY = _y >= 0 ? _y % CHUNK_SIZE : CHUNK_SIZE - ((-1 - _y) % CHUNK_SIZE) - 1;

	if (chunkMap[chunkX - x][chunkY - y] == NULL) {
		return;
	}

	chunkMap[chunkX - x][chunkY - y]->setTile(tile, tileX, tileY);
}

Tile* World::getTile(float _x, float _y) {
	int i_x = (int)floor((float)_x / TILE_SIZE);
	int i_y = (int)floor((float)_y / TILE_SIZE);
	int chunkX = (int)floor((float)i_x / CHUNK_SIZE);
	int chunkY = (int)floor((float)i_y / CHUNK_SIZE);


	int tileX = _x >= 0 ? i_x % CHUNK_SIZE : CHUNK_SIZE - (-i_x % CHUNK_SIZE);
	int tileY = _y >= 0 ? i_y % CHUNK_SIZE : CHUNK_SIZE - (-i_y % CHUNK_SIZE);

	if (chunkMap[chunkX - x][chunkY - y] == NULL) {
		return NULL;
	}
	return chunkMap[chunkX - x][chunkY - y]->getTile(tileX, tileY);
}

void World::snapToGrid(float* x, float* y) {
	*x = floorf(*x / TILE_SIZE) * TILE_SIZE;
	*y = floorf(*y / TILE_SIZE) * TILE_SIZE;
}