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
		void draw(SDL_Renderer* renderer, float mouseX, float mouseY);
		int insertItem(Item* type, int amount);
		void setItem(ItemStack* itemStack, int slotX, int slotY);
		int countItem(Item* type);
		int takeItem(Item* type, int amount);
		ItemStack* getSlot(float x, float y, int* slotX, int* slotY);
		bool getSlotValid(float x, float y, int* slotX, int* slotY);
		// ADD INTERRACTION FUNCTIONS HERE
};

void drawUIBackground(SDL_Renderer* renderer, float x, float y, float width, float height); // UI element drawing Utility
void drawTextString(SDL_Renderer* renderer, float x, float y, char* string, int stringLength);
void drawTextStrings(SDL_Renderer* renderer, float x, float y, char** string, int lineCount, int maxStringLength);