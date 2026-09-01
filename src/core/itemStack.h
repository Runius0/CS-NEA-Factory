#pragma once
#include "../../core.h"
#include "item.h"

class ItemStack {
	int amount;

	public:
		Item* type;
		ItemStack(Item* type, int amount);

		bool operator==(const ItemStack* other);
		int getAmount();
		int add(int amount); // returns the amount of items actually added to the stack
		int take(int amount); // returns the amount of items taken from the stack
		bool takeStrict(int amount); // returns success, will not take unless required items are available
};
