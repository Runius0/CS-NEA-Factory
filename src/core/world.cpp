#include "world.h"

World::World() {
	x = -5;
	y = -5;
};

void World::draw(float _x, float _y) {
	int chunkX = (int)(_x / CHUNK_SIZE);
	int chunkY = (int)(_y / CHUNK_SIZE);
	
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (&chunkMap[i - x + chunkX][j - y + chunkY]) {
				chunkMap[i - x + chunkX][j - y + chunkY].draw(_x, _y);
			}
		}
	}
};