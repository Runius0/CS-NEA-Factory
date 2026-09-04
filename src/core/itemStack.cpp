#include "itemStack.h"

ItemStack::ItemStack(Item* _type, int _amount) {
	amount = _amount;
	type = _type;
}


bool ItemStack::operator==(const ItemStack other) {
	return (type == other.type);
}

int ItemStack::getAmount() {
	return amount;
}

int ItemStack::getSpace() {
	return type->maxStack - amount;
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


bool ItemStack::addStrict(int val) {
	if (val + amount > type->maxStack) {
		return false;
	}
	amount += val;
	return true;
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


void ItemStack::draw(SDL_Renderer* renderer, float x, float y, int scale) {
	type->draw(renderer, x, y, scale);
	float numStartY = y + SPRITE_SIZE*scale - 7*scale;
	int rollingNumber = amount;
	SDL_FRect tileRect, texRect;
	int i = 1;
	while (rollingNumber > 0)
	{
		texRect = { SPRITE_SIZE * 3 + (float)(rollingNumber % 10)*5, SPRITE_SIZE, 5, 7};
		tileRect = { x + SPRITE_SIZE*scale - i * 5*scale, numStartY, (float)5 * scale, (float)7 * scale };
		SDL_RenderTexture(renderer, textureList[TEX_UI], &texRect, &tileRect);
		i++;
		rollingNumber /= 10;
	}
};