#include "uiElement.h"

void drawUIBackground(SDL_Renderer* renderer, float x, float y, float width, float height) {

	SDL_FRect tileRect, texRect;
	// draw border
	// top
	texRect = { SPRITE_SIZE, SPRITE_SIZE - 1, SPRITE_SIZE, 1 };
	tileRect = { x, y - 1 * UI_SCALE * UI_SLOT_SCALE, width, 1 * UI_SCALE * UI_SLOT_SCALE };
	SDL_RenderTexture(renderer, textureList[TEX_UI], &texRect, &tileRect);

	// bottom
	texRect = { SPRITE_SIZE, SPRITE_SIZE * 2, SPRITE_SIZE, 3 };
	tileRect = { x, y + height, width, 3 * UI_SCALE * UI_SLOT_SCALE };
	SDL_RenderTexture(renderer, textureList[TEX_UI], &texRect, &tileRect);

	// left
	texRect = { SPRITE_SIZE - 1, SPRITE_SIZE, 1, SPRITE_SIZE };
	tileRect = { x - 1 * UI_SCALE * UI_SLOT_SCALE, y, 1 * UI_SCALE * UI_SLOT_SCALE, height };
	SDL_RenderTexture(renderer, textureList[TEX_UI], &texRect, &tileRect);

	// right
	texRect = { SPRITE_SIZE * 2, SPRITE_SIZE, 1, SPRITE_SIZE };
	tileRect = { x + width, y, 1 * UI_SCALE * UI_SLOT_SCALE, height };
	SDL_RenderTexture(renderer, textureList[TEX_UI], &texRect, &tileRect);

	// bottom-left
	texRect = { SPRITE_SIZE - 1, SPRITE_SIZE * 2, 1, 2 };
	tileRect = { x - 1 * UI_SCALE * UI_SLOT_SCALE, y + height, 1 * UI_SCALE * UI_SLOT_SCALE, 2 * UI_SCALE * UI_SLOT_SCALE };
	SDL_RenderTexture(renderer, textureList[TEX_UI], &texRect, &tileRect);

	// bottom-right
	texRect = { SPRITE_SIZE * 2, SPRITE_SIZE * 2, 1, 2 };
	tileRect = { x + width, y + height, 1 * UI_SCALE * UI_SLOT_SCALE, 2 * UI_SCALE * UI_SLOT_SCALE };
	SDL_RenderTexture(renderer, textureList[TEX_UI], &texRect, &tileRect);

	//centre
	tileRect = { x, y, width, height };
	SDL_SetRenderDrawColor(renderer, 74, 84, 98, 255);
	SDL_RenderFillRect(renderer, &tileRect);

}


UIElement::UIElement(float _x, float _y, int _width, int _height) {
	x = _x;
	y = _y;
	width = _width;
	height = _height;

	// I wish there was an easier way but compiler complains if I try to do it on one step
	items = new ItemStack ** [width];
	for (int i = 0; i < width; i++) {
		items[i] = new ItemStack * [height];
		for (int j = 0; j < height; j++) {
			items[i][j] = NULL;
		}
	}
}

void UIElement::draw(SDL_Renderer* renderer) {

	// draw slots
	SDL_FRect tileRect, texRect;
	texRect = { SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE };
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			tileRect = { x + i * SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE, y + j * SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE, SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE, SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE };
			SDL_RenderTexture(renderer, textureList[TEX_UI], &texRect, &tileRect);
			if (items[i][j] != NULL) {
				items[i][j]->draw(renderer, x + i * SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE, y + j * SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE, 2);
			}
		}
	}

	// draw border
	// top
	texRect = { SPRITE_SIZE, SPRITE_SIZE - 1, SPRITE_SIZE, 1 };
	tileRect = { x, y - 1 * UI_SCALE * UI_SLOT_SCALE, (float)(width * SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE), 1 * UI_SCALE * UI_SLOT_SCALE };
	SDL_RenderTexture(renderer, textureList[TEX_UI], &texRect, &tileRect);

	// bottom
	texRect = { SPRITE_SIZE, SPRITE_SIZE * 2, SPRITE_SIZE, 3};
	tileRect = { x, y + height * SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE, (float)(width * SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE), 3 * UI_SCALE * UI_SLOT_SCALE };
	SDL_RenderTexture(renderer, textureList[TEX_UI], &texRect, &tileRect);

	// left
	texRect = { SPRITE_SIZE - 1, SPRITE_SIZE, 1, SPRITE_SIZE };
	tileRect = { x - 1 * UI_SCALE * UI_SLOT_SCALE, y, 1 * UI_SCALE * UI_SLOT_SCALE, (float)(height * SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE) };
	SDL_RenderTexture(renderer, textureList[TEX_UI], &texRect, &tileRect);

	// right
	texRect = { SPRITE_SIZE * 2, SPRITE_SIZE, 1, SPRITE_SIZE };
	tileRect = { x + width * SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE, y, 1 * UI_SCALE * UI_SLOT_SCALE, (float)(height * SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE) };
	SDL_RenderTexture(renderer, textureList[TEX_UI], &texRect, &tileRect);

	// bottom-left
	texRect = { SPRITE_SIZE - 1, SPRITE_SIZE * 2, 1, 2 };
	tileRect = { x - 1 * UI_SCALE * UI_SLOT_SCALE, y + height * SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE, 1 * UI_SCALE * UI_SLOT_SCALE, 2 * UI_SCALE * UI_SLOT_SCALE };
	SDL_RenderTexture(renderer, textureList[TEX_UI], &texRect, &tileRect);

	// bottom-right
	texRect = { SPRITE_SIZE * 2, SPRITE_SIZE * 2, 1, 2 };
	tileRect = { x + width * SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE, y + height * SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE, 1 * UI_SCALE * UI_SLOT_SCALE, 2 * UI_SCALE * UI_SLOT_SCALE };
	SDL_RenderTexture(renderer, textureList[TEX_UI], &texRect, &tileRect);
}


void UIElement::draw(SDL_Renderer* renderer, float mouseX, float mouseY) {

	// draw slots
	SDL_FRect tileRect, texRect;
	texRect = { SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE };
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			tileRect = { x + i * SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE, y + j * SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE, SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE, SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE };
			SDL_RenderTexture(renderer, textureList[TEX_UI], &texRect, &tileRect);
			if (items[i][j] != NULL) {
				items[i][j]->draw(renderer, x + i * SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE, y + j * SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE, 2);
			}
		}
	}

	// draw border
	// top
	texRect = { SPRITE_SIZE, SPRITE_SIZE - 1, SPRITE_SIZE, 1 };
	tileRect = { x, y - 1 * UI_SCALE * UI_SLOT_SCALE, (float)(width * SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE), 1 * UI_SCALE * UI_SLOT_SCALE };
	SDL_RenderTexture(renderer, textureList[TEX_UI], &texRect, &tileRect);

	// bottom
	texRect = { SPRITE_SIZE, SPRITE_SIZE * 2, SPRITE_SIZE, 3 };
	tileRect = { x, y + height * SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE, (float)(width * SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE), 3 * UI_SCALE * UI_SLOT_SCALE };
	SDL_RenderTexture(renderer, textureList[TEX_UI], &texRect, &tileRect);

	// left
	texRect = { SPRITE_SIZE - 1, SPRITE_SIZE, 1, SPRITE_SIZE };
	tileRect = { x - 1 * UI_SCALE * UI_SLOT_SCALE, y, 1 * UI_SCALE * UI_SLOT_SCALE, (float)(height * SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE) };
	SDL_RenderTexture(renderer, textureList[TEX_UI], &texRect, &tileRect);

	// right
	texRect = { SPRITE_SIZE * 2, SPRITE_SIZE, 1, SPRITE_SIZE };
	tileRect = { x + width * SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE, y, 1 * UI_SCALE * UI_SLOT_SCALE, (float)(height * SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE) };
	SDL_RenderTexture(renderer, textureList[TEX_UI], &texRect, &tileRect);

	// bottom-left
	texRect = { SPRITE_SIZE - 1, SPRITE_SIZE * 2, 1, 2 };
	tileRect = { x - 1 * UI_SCALE * UI_SLOT_SCALE, y + height * SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE, 1 * UI_SCALE * UI_SLOT_SCALE, 2 * UI_SCALE * UI_SLOT_SCALE };
	SDL_RenderTexture(renderer, textureList[TEX_UI], &texRect, &tileRect);

	// bottom-right
	texRect = { SPRITE_SIZE * 2, SPRITE_SIZE * 2, 1, 2 };
	tileRect = { x + width * SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE, y + height * SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE, 1 * UI_SCALE * UI_SLOT_SCALE, 2 * UI_SCALE * UI_SLOT_SCALE };
	SDL_RenderTexture(renderer, textureList[TEX_UI], &texRect, &tileRect);

	int slotX = (int)SDL_floorf((mouseX - x) / (SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE));
	int slotY = (int)SDL_floorf((mouseY - y) / (SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE));
	if (slotX < 0 || slotY < 0 || slotX >= width || slotY >= height) {
		return;
	}
	texRect = { SPRITE_SIZE * 3, 0, SPRITE_SIZE, SPRITE_SIZE };
	tileRect = { x + slotX * SPRITE_SIZE * UI_SCALE, y + slotY * SPRITE_SIZE * UI_SCALE, SPRITE_SIZE * UI_SCALE, SPRITE_SIZE * UI_SCALE };
	SDL_RenderTexture(renderer, textureList[TEX_UI], &texRect, &tileRect);


}


ItemStack* UIElement::getSlot(float _x, float _y, int* _slotX, int* _slotY) {
	int slotX = (int)SDL_floorf((_x - x) / (SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE));
	int slotY = (int)SDL_floorf((_y - y) / (SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE));
	if (slotX < 0 || slotY < 0 || slotX >= width || slotY >= height) {
		return NULL;
	}
	*_slotX = slotX;
	*_slotY = slotY;
	return items[slotX][slotY];
};

bool UIElement::getSlotValid(float _x, float _y, int* _slotX, int* _slotY) {
	int slotX = (int)SDL_floorf((_x - x) / (SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE));
	int slotY = (int)SDL_floorf((_y - y) / (SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE));
	if (slotX < 0 || slotY < 0 || slotX >= width || slotY >= height) {
		return false;
	}
	*_slotX = slotX;
	*_slotY = slotY;
	return true;
};

void UIElement::setItem(ItemStack* itemStack, int slotX, int slotY) {
	items[slotX][slotY] = itemStack;
};

int UIElement::insertItem(Item* type, int amount) {
	int amountRemaining = amount;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (items[i][j] != NULL && items[i][j]->type == type) {
				amountRemaining -= items[i][j]->add(amountRemaining);
			}
			if (amountRemaining == 0) {
				return amount;
			}
		}
	}
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (items[i][j] == NULL) {
				items[i][j] = new ItemStack(type, amountRemaining);
				return amount;
			}
		}
	}
	return amount - amountRemaining;

	
};