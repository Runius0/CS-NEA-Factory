#pragma once
#include "../../core.h"
#include "itemStack.h"

const int UI_SCALE = 2;
const int UI_SLOT_SCALE = 1; // scale of the slot compared to items. technically mixels, but I don't care.
// x and y coordinates refer to top left corner of the top left slot, border is not included

class UIElement {
	float x;
	float y;
	int width, height;
	public:
		// TAKE THIS OUT OF PUBLIC PLEASE
		ItemStack*** items; // 2D array of pointers to itemStacks contained within the inventory
		UIElement(float x, float y, int width, int height);
		void draw(SDL_Renderer* renderer);
		// ADD INTERRACTION FUNCTIONS HERE
};