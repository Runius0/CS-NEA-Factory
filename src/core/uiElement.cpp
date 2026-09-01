#include "uiElement.h"

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
				items[i][j]->type->draw(renderer, x + i * SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE, y + j * SPRITE_SIZE * UI_SCALE * UI_SLOT_SCALE, 2);
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