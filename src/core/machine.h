#pragma once
#include "tile.h"

// to allow the machine to interract with the world
#include "world.h"

class Machine : public Tile {
	public:
		const bool solid = true;
		Direction direction;
		int width = 1;
		int height = 1;
		Machine(int worldX, int worldY);
		void clear(World* world); // delete machine from world
		void place(World* world); // fill in all necessary tiles
		static bool canPlace(World* world, int worldX, int worldY, int width, int height);
		static void DrawPreview(SDL_Renderer* renderer, float x, float y);
};