#include "item.h"


Item* ITEM[256];

static int nextID = 1; // ID 0 is no item

Item::Item(char* _name, SDL_FRect _sprite, int _maxStack) {
	sprite = _sprite;
	strcpy_s(name, _name);
	maxStack = _maxStack;
	ID = nextID;
	nextID++;
}

Item::Item() {
	sprite = { 0, 0, SPRITE_SIZE, SPRITE_SIZE };
	strcpy_s(name, "ERROR");
	maxStack = 1;
	ID = 255;
}

void Item::draw(SDL_Renderer* renderer, float x, float y, int scale) {
	SDL_FRect destRect = {x, y, SPRITE_SIZE * scale, SPRITE_SIZE * scale}; // really should put the scaling constant somewhere
	SDL_RenderTexture(renderer, textureList[TEX_ITEM], &sprite, &destRect);
}