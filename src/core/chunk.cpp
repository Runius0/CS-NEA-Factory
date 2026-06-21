#include "chunk.h"

Chunk::Chunk(int _x, int _y) {
	x = _x;
	y = _y;
};

void Chunk::draw(SDL_Renderer* renderer, float _x, float _y) {
	int chunkX = (x * CHUNK_SIZE_PX) - _x;
	int chunkY = (y * CHUNK_SIZE_PX) - _y;
	SDL_FRect chunkRect = { chunkX + SCREEN_WIDTH/2, chunkY + SCREEN_HEIGHT / 2, CHUNK_SIZE_PX, CHUNK_SIZE_PX };
	SDL_SetRenderDrawColor(renderer, 128 + x * 8, 128 + y * 8, 128, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &chunkRect);
};