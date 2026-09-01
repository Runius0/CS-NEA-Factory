#pragma once
#include "../../core.h"



class Item {
	SDL_FRect sprite;

	public:
		int ID;
		int maxStack;
		char name[32]; // 32 letters for your name, that's all you get
		Item(char* name, SDL_FRect sprite, int maxStack);
		Item();
		void draw(SDL_Renderer* renderer, float x, float y, int scale = 1);
};

extern Item* ITEM[256]; // declared here so classes can access the index