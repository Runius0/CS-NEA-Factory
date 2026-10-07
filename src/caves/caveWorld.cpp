#include "caveWorld.h"


CaveWorld::CaveWorld() : World() {
};
void CaveWorld::addChunk(int _x, int _y) {
	chunkMap[_x - x][_y - y] = new CaveChunk(_x, _y);
};

CaveChunk::CaveChunk(int _x, int _y) : Chunk() {
	x = _x;
	y = _y;
	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			if (i > 2 && i + j < 40 && j > 6) { // test generation
				tileMap[i][j] = new CaveDirt(i + x * CHUNK_SIZE, j + y * CHUNK_SIZE);
			}
			else {
				tileMap[i][j] = new CaveWall(i + x * CHUNK_SIZE, j + y * CHUNK_SIZE);
			}
		}
	}
};