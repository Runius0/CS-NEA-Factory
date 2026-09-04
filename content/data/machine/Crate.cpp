#include "Crate.h"

Crate::Crate(int _worldX, int _worldY, Direction direction) : Machine(_worldX, _worldY, direction) {
	width = 1;
	height = 1;
	ID = 4;
	inventory = new UIElement(0, 0, 2, 2);
};

void Crate::draw(SDL_Renderer* renderer, float _x, float _y) {

	SDL_FRect tileRect = { _x, _y, TILE_SIZE, TILE_SIZE };
	SDL_FRect texRect = { SPRITE_SIZE * 4, SPRITE_SIZE * 3, SPRITE_SIZE, SPRITE_SIZE };
	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);

}

ItemStack* Crate::extractItem() {
	for (int i = 0; i < 4; i++) {
		if (inventory->items[i % 2][i / 2] != NULL) {
			Item* itemType = inventory->items[i % 2][i / 2]->type;
			inventory->takeItem(itemType, 1);
			return new ItemStack(itemType, 1);
		}
	}
	return NULL;
}

bool Crate::acceptItem(ItemStack* item, int x, int y, Direction direction, bool forced) {
	if (forced && inventory->insertItem(item->type, 1)) {
		return true;
	}
	return false;
};

void Crate::DrawPreview(SDL_Renderer* renderer, float _x, float _y, Direction _direction) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);

	SDL_FRect tileRect = { _x, _y, TILE_SIZE, TILE_SIZE };
	SDL_FRect texRect = { SPRITE_SIZE * 4, SPRITE_SIZE * 3, SPRITE_SIZE, SPRITE_SIZE };

	SDL_SetTextureAlphaMod(textureList[TEX_TILES1], 128);
	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);
	SDL_SetTextureAlphaMod(textureList[TEX_TILES1], 255);
}


void Crate::renderInventory(SDL_Renderer* renderer, float x, float y, float mouseX, float mouseY) {
	inventory->setPos(x, y);
	inventory->draw(renderer, mouseX, mouseY);
}


void Crate::clickInventory(UIElement* playerHotbar, UIElement* playerInventory, ItemStack** cursorItem, float x, float y, float mouseX, float mouseY) {
	inventory->setPos(x, y);
	int slotX, slotY;
	if (inventory->getSlotValid(mouseX, mouseY, &slotX, &slotY)) {
		if (*cursorItem == NULL || inventory->items[slotX][slotY] == NULL) {
			ItemStack* temp = *cursorItem;
			*cursorItem = inventory->items[slotX][slotY];
			inventory->setItem(temp, slotX, slotY);
		}
		else if (**cursorItem == *inventory->items[slotX][slotY]) {
			(*cursorItem)->take(inventory->items[slotX][slotY]->add((*cursorItem)->getAmount()));
			if ((*cursorItem)->getAmount() == 0) {
				(*cursorItem) = NULL;
			}
		}
	}

};