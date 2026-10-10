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
			tileMap[i][j] = new CaveWall(i + x * CHUNK_SIZE, j + y * CHUNK_SIZE);
		}
	}
};

void CaveWorld::setTile(Tile* tile, int _x, int _y) {
	int chunkX = (int)floor((float)_x / CHUNK_SIZE);
	int chunkY = (int)floor((float)_y / CHUNK_SIZE);

	int tileX = _x >= 0 ? _x % CHUNK_SIZE : CHUNK_SIZE - ((-1 - _x) % CHUNK_SIZE) - 1;
	int tileY = _y >= 0 ? _y % CHUNK_SIZE : CHUNK_SIZE - ((-1 - _y) % CHUNK_SIZE) - 1;
	// modulus can fuck up in negative chunks, dirty fix
	if (tileX == CHUNK_SIZE) { tileX = 0; }
	if (tileY == CHUNK_SIZE) { tileY = 0; }

	if (chunkMap[chunkX - x][chunkY - y] == NULL) {
		chunkMap[chunkX - x][chunkY - y] = new CaveChunk(chunkX, chunkY);
	}

	chunkMap[chunkX - x][chunkY - y]->setTile(tile, tileX, tileY);
}