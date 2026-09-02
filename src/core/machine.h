#pragma once
#include "tile.h"
#include "itemStack.h"

// to allow the machine to interract with the world
#include "world.h"

class Machine : public Tile {
	public:
		Direction direction;
		int width = 1;
		int height = 1;
		Machine(int worldX, int worldY, Direction direction);
		void clear(World* world); // delete machine from world
		void place(World* world); // fill in all necessary tiles
		static bool canPlace(World* world, int worldX, int worldY, int width, int height);
		static void DrawPreview(SDL_Renderer* renderer, float x, float y, Direction direction);

		// conveyor interaction handlers
		virtual bool acceptItem(ItemStack* item, int x, int y, Direction direction, bool forced) { return false; };
		virtual ItemStack* extractItem() { return NULL; };
};