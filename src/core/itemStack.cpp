#include "itemStack.h"

ItemStack::ItemStack(Item* _type, int _amount) {
	amount = _amount;
	type = _type;
}


bool ItemStack::operator==(const ItemStack* other) {
	return (type == other->type);
}

int ItemStack::getAmount() {
	return amount;
}

int ItemStack::add(int val) {
	int itemSpace = type->maxStack - amount;
	amount += val;
	if (val > itemSpace) {
		amount = type->maxStack;
		return itemSpace;
	}
	return val;
}

int ItemStack::take(int val) {
	if (val > amount) {
		int amountTaken = amount;
		amount = 0;
		return amountTaken;
	}
	amount -= val;
	return val;
}

bool ItemStack::takeStrict(int val) {
	if (val > amount) {
		return false;
	}
	amount -= val;
	return true;
}
