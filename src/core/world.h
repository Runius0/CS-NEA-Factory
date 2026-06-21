#include "chunk.h"
class World {
	Chunk chunkMap[11][11];

	// coordinates of top left chunk
	int x;
	int y;
public:
	// functions
	World();

	void addChunk(int x, int y);
	// Tile getTile(int _x, int _y);
	//bool isSpaceOccupied(int _x, int _y, int width, int height);
	void draw(float x, float y);
	void tick();
};