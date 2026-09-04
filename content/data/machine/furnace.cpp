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

	return toReturn;
}

void Furnace::renderInventory(SDL_Renderer* renderer, float x, float y, float mouseX, float mouseY) {
	drawUIBackground(renderer, x, y, 192, 128);
	SDL_FRect srcRect = { SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE };
	SDL_FRect dstRect = {x + 16, y + 32, SPRITE_SIZE * UI_SCALE, SPRITE_SIZE * UI_SCALE };
	SDL_RenderTexture(renderer, textureList[TEX_UI], &srcRect, &dstRect);
	if (inputItem != NULL) { inputItem->draw(renderer, x + 16, y + 32, 2); }
	

	dstRect = { x + 144, y + 32, SPRITE_SIZE * UI_SCALE, SPRITE_SIZE * UI_SCALE };
	SDL_RenderTexture(renderer, textureList[TEX_UI], &srcRect, &dstRect);
	if (outputItem != NULL) { outputItem->draw(renderer, x + 144, y + 32, 2); }
	

	srcRect = { SPRITE_SIZE*4, 0, SPRITE_SIZE, SPRITE_SIZE };
	dstRect = { x + 80, y + 32, SPRITE_SIZE*UI_SCALE, SPRITE_SIZE * UI_SCALE };
	SDL_RenderTexture(renderer, textureList[TEX_UI], &srcRect, &dstRect);

	SDL_SetRenderDrawColor(renderer, 51, 57, 65, 255);
	dstRect = { x + 16, y + 64, 160, 4 };
	SDL_RenderFillRect(renderer, &dstRect);
	if (currentRecipe != NULL) {
		SDL_SetRenderDrawColor(renderer, 180, 32, 42, 255);
		dstRect = { x + 16, y + 64, 160 * ((float)craftingTicks / (float)currentRecipe->getTime()), 4};
		SDL_RenderFillRect(renderer, &dstRect);
	}

	float rx = mouseX - x;
	float ry = mouseY - y;
	srcRect = { SPRITE_SIZE * 3, 0, SPRITE_SIZE, SPRITE_SIZE };
	if (rx > 16 && rx < 48 && ry > 32 && ry < 64) {
		dstRect = { x + 16, y + 32, SPRITE_SIZE * UI_SCALE, SPRITE_SIZE * UI_SCALE };
		SDL_RenderTexture(renderer, textureList[TEX_UI], &srcRect, &dstRect);

	}

	if (rx > 144 && rx < 176 && ry > 32 && ry < 64) {
		dstRect = { x + 144, y + 32, SPRITE_SIZE * UI_SCALE, SPRITE_SIZE * UI_SCALE };
		SDL_RenderTexture(renderer, textureList[TEX_UI], &srcRect, &dstRect);

	}
}


void Furnace::clickInventory(UIElement* playerHotbar, UIElement* playerInventory, ItemStack** cursorItem, float x, float y, float mouseX, float mouseY) {
	float rx = mouseX - x;
	float ry = mouseY - y;
	if (rx > 16 && rx < 48 && ry > 32 && ry < 64) {
		if (inputItem != NULL && *cursorItem != NULL && *inputItem == **cursorItem) {
			(*cursorItem)->take(inputItem->add((*cursorItem)->getAmount()));
			if ((*cursorItem)->getAmount() == 0) {
				*cursorItem = NULL;
			}
		}
		else {
			ItemStack* temp = *cursorItem;
			*cursorItem = inputItem;
			inputItem = temp;
		}
	}

	if (rx > 144 && rx < 176 && ry > 32 && ry < 64) {
		if (outputItem != NULL && *cursorItem != NULL && *outputItem == **cursorItem) {
			outputItem->take((*cursorItem)->add(outputItem->getAmount()));
			if (outputItem->getAmount() == 0) {
				outputItem = NULL;
			}
		}
		else if (*cursorItem == NULL) {
			*cursorItem = outputItem;
			outputItem = NULL;
		}
	}

};

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