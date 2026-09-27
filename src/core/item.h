#pragma once
#include "../../core.h"
#include "world.h"
#include "player.h"


class Item {
	SDL_FRect sprite;

	public:
		int ID;
		int maxStack;
		bool placeable = false;
		char name[32]; // 32 letters for your name, that's all you get
		Item(char* name, SDL_FRect sprite, int maxStack);
		Item();
		void draw(SDL_Renderer* renderer, float x, float y, int scale = 1);
		virtual bool interact(World* world, int worldX, int worldY, int* stackSize, Player* playerInfo) { return false; };
};

extern Item* ITEM[256]; // declared here so classes can access the index