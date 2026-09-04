#include "furnace.h"

Furnace::Furnace(int _worldX, int _worldY, Direction direction) : Machine(_worldX, _worldY, Right) {
	width = 2;
	height = 2;
	ID = 6;
	inputItem = NULL;
	outputItem = NULL;
};

void Furnace::draw(SDL_Renderer* renderer, float _x, float _y) {

	SDL_FRect tileRect = { _x, _y, TILE_SIZE * 2, TILE_SIZE * 2 };
	SDL_FRect texRect = { SPRITE_SIZE * ((int)(currentRecipe != NULL)*2 + 2), 0, SPRITE_SIZE * 2, SPRITE_SIZE * 2 };
	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);

}

void Furnace::tick(World* world, int gameTick) {
	if (inputItem != NULL && currentRecipe == NULL) {
		ItemStack* requiredItem;
		ItemStack* output;
		for (int i = 0; i < numRecipes[SMELT]; i++) {
			requiredItem = recipeRegistry[SMELT][i]->getIngredients()[0];
			output = recipeRegistry[SMELT][i]->getResult();
			if (requiredItem->type == inputItem->type && requiredItem->getAmount() <= inputItem->getAmount() && (outputItem == NULL || (output->type == outputItem->type && output->getAmount() < outputItem->getSpace()))) {
				craftingTicks = 0;
				currentRecipe = recipeRegistry[SMELT][i];
				break;
			}
		}
	}
	else if (currentRecipe != NULL) {
		ItemStack* requiredItem = currentRecipe->getIngredients()[0];
		craftingTicks++;
		if (inputItem == NULL || requiredItem->type != inputItem->type || requiredItem->getAmount() > inputItem->getAmount() || !(outputItem == NULL || (currentRecipe->getResult()->type == outputItem->type && currentRecipe->getResult()->getAmount() < outputItem->getSpace()))) {
			craftingTicks = 0;
			currentRecipe = NULL;
		}
		else if (craftingTicks >= currentRecipe->getTime()) {
			inputItem->take(requiredItem->getAmount());
			if (inputItem->getAmount() == 0) {
				inputItem = NULL;
			}
			if (outputItem == NULL) {
				outputItem = new ItemStack(*currentRecipe->getResult());
			}
			else {
				outputItem->add(currentRecipe->getResult()->getAmount());
			}
			currentRecipe = NULL;
		}
	}
}

ItemStack* Furnace::extractItem() {
	if (outputItem == NULL) {
		return NULL;
	}
	ItemStack* toReturn = new ItemStack(outputItem->type, 1);
	outputItem->take(1);
	if (outputItem->getAmount() == 0) {
		outputItem = NULL;
	}

	return new ItemStack(ITEM[ID], 1);
}

void Furnace::processInventory(SDL_Renderer* renderer, UIElement* playerHotbar, UIElement* playerInventory, ItemStack** cursorItem, float x, float y, float mouseX, float mouseY) {
	drawUIBackground(renderer, x, y, 192, 128);
}

bool Furnace::acceptItem(ItemStack* item, int x, int y, Direction direction, bool forced) {
	if (!forced) {
		return false;
	}
	if (inputItem == NULL) {
		inputItem = item;
		return true;
	}
	if (inputItem->type == item->type) {
		return inputItem->addStrict(item->getAmount());
	}
	return false;
}

void Furnace::DrawPreview(SDL_Renderer* renderer, float _x, float _y, Direction _direction) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);

	SDL_FRect tileRect = { _x, _y, TILE_SIZE*2, TILE_SIZE*2};
	SDL_FRect texRect = { SPRITE_SIZE * 2, 0, SPRITE_SIZE*2, SPRITE_SIZE*2 };

	SDL_SetTextureAlphaMod(textureList[TEX_TILES1], 128);
	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);
	SDL_SetTextureAlphaMod(textureList[TEX_TILES1], 255);
}