#pragma once
#include "../../core.h"
#include "item.h"

class ItemStack {
	int amount;

	public:
		Item* type;
		ItemStack(Item* type, int amount);
		ItemStack();

		bool operator==(const ItemStack other);
		int getAmount();
		int getSpace();
		void setAmount(int amount);
		int add(int amount); // returns the amount of items actually added to the stack
		int add(int amount, Item* type); // returns the amount of items actually added to the stack
		int take(int amount); // returns the amount of items taken from the stack
		bool addStrict(int val);
		bool addStrict(int val, Item* type);
		bool takeStrict(int amount); // returns success, will not take unless required items are available
		bool interact(World* world, int worldX, int worldY, Player* playerInfo);
		bool isNull();
		void draw(SDL_Renderer* renderer, float x, float y, int scale = 1);
};
