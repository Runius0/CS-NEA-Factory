#include "chunk.h"
#include "world.h"

Chunk::Chunk(int _x, int _y) {

	x = _x;
	y = _y;
	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			tileMap[i][j] = new Grass(i + x * CHUNK_SIZE, j + y * CHUNK_SIZE);
		}
	}
};

void Chunk::draw(SDL_Renderer* renderer, float _x, float _y) {
	int chunkX = (x * CHUNK_SIZE_PX) - _x;
	int chunkY = (y * CHUNK_SIZE_PX) - _y;

	int chunk_tileX = (x * CHUNK_SIZE);
	int chunk_tileY = (y * CHUNK_SIZE);

	SDL_FRect chunkRect = { chunkX + SCREEN_WIDTH/2, chunkY + SCREEN_HEIGHT / 2, CHUNK_SIZE_PX, CHUNK_SIZE_PX };

	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			if (chunk_tileX + i == tileMap[i][j]->worldX && chunk_tileY + j == tileMap[i][j]->worldY) {
				tileMap[i][j]->draw(renderer, chunkX + SCREEN_WIDTH / 2 + i * TILE_SIZE, chunkY + SCREEN_HEIGHT / 2 + j * TILE_SIZE);
			}
		}
	}
};
void Chunk::drawOverlay(SDL_Renderer* renderer, float _x, float _y) {
	int chunkX = (x * CHUNK_SIZE_PX) - _x;
	int chunkY = (y * CHUNK_SIZE_PX) - _y;

	int chunk_tileX = (x * CHUNK_SIZE);
	int chunk_tileY = (y * CHUNK_SIZE);

	SDL_FRect chunkRect = { chunkX + SCREEN_WIDTH / 2, chunkY + SCREEN_HEIGHT / 2, CHUNK_SIZE_PX, CHUNK_SIZE_PX };

	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			if (chunk_tileX + i == tileMap[i][j]->worldX && chunk_tileY + j == tileMap[i][j]->worldY) {
				tileMap[i][j]->drawOverlay(renderer, chunkX + SCREEN_WIDTH / 2 + i * TILE_SIZE, chunkY + SCREEN_HEIGHT / 2 + j * TILE_SIZE);
			}
		}
	}
};


void Chunk::tick(World* world, int gameTick) {
	int chunk_tileX = (x * CHUNK_SIZE);
	int chunk_tileY = (y * CHUNK_SIZE);

	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			if (chunk_tileX + i == tileMap[i][j]->worldX && chunk_tileY + j == tileMap[i][j]->worldY) {
				tileMap[i][j]->tick(world, gameTick);
			}
		}
	}
};

Tile* Chunk::getTile(int _x, int _y) {
	return tileMap[_x][_y];
}
void Chunk::setTile(Tile* tile, int _x, int _y) {
	tileMap[_x][_y] = tile;
}