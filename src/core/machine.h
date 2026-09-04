#pragma once
#include "tile.h"
#include "itemStack.h"
#include "UIElement.h"

// to allow the machine to interract with the world
#include "world.h"

class Machine : public Tile {
	public:
		Direction direction;
		int width = 1;
		int height = 1;
		int ID = 0;
		Machine(int worldX, int worldY, Direction direction);
		void clear(World* world); // delete machine from world
		void place(World* world); // fill in all necessary tiles
		static bool canPlace(World* world, int worldX, int worldY, int width, int height);
		static void DrawPreview(SDL_Renderer* renderer, float x, float y, Direction direction);

		virtual bool interract() {
			return false;
		} // return true if machine has an inventory, else return false

		virtual void renderInventory(SDL_Renderer* renderer, float x, float y, float mouseX, float mouseY) {};
		virtual void clickInventory(UIElement* playerHotbar, UIElement* playerInventory, ItemStack** cursorItem, float x, float y, float mouseX, float mouseY) {};

		// conveyor interaction handlers
		virtual bool acceptItem(ItemStack* item, int x, int y, Direction direction, bool forced) { return false; };
		virtual ItemStack* extractItem() { return NULL; };
};