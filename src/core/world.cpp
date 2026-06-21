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
	int chunkX = (int)(_x / CHUNK_SIZE);
	int chunkY = (int)(_y / CHUNK_SIZE);
	


	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if ((i - x + chunkX >= 0) && (i - x + chunkX < std::size(chunkMap)) && chunkMap[i - x + chunkX][j - y + chunkY]) {
				chunkMap[i - x + chunkX][j - y + chunkY]->draw(renderer, _x, _y);
			}
		}
	}
};