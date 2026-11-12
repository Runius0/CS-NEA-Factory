#include "assembler.h"

Crafter::Crafter() : Machine() {
	width = 2;
	height = 2;
	outputItem = NULL;
	flags |= T_SOLID | T_USESITEMS;
	maxIngredients = 2;
	recipeFilter = CRAFT;
};


void Crafter::draw(SDL_Renderer* renderer, float _x, float _y) {

	SDL_FRect tileRect = { _x, _y, TILE_SIZE * 2, TILE_SIZE * 2 };
	SDL_FRect texRect = { SPRITE_SIZE * 2, 0, SPRITE_SIZE * 2, SPRITE_SIZE * 2 };
	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);

}

Machine* Crafter::copy(int _worldX, int _worldY, Direction _direction) {
	Machine* out = new Crafter();
	out->init(_worldX, _worldY, _direction);
	out->ID = ID;
	return out;
};

void Crafter::tick(World* world, int gameTick) {
	if (state == STATE_A_RECIPECHOOSE) { return; }

	bool craftValid = true;
	for (int i = 0; i < maxIngredients; i++) {
		if (recipeRegistry[recipeFilter][selectedRecipe]->getIngredients()[i] == NULL) {
			break;
		}
		if (inputItems[i] == NULL || inputItems[i]->getAmount() < recipeRegistry[recipeFilter][selectedRecipe]->getIngredients()[i]->getAmount()) {
			craftValid = false;
		}
		if (inputItems[i] == NULL || !(*inputItems[i] == *recipeRegistry[recipeFilter][selectedRecipe]->getIngredients()[i])) {
			craftValid = false;
		}
	}
	if (outputItem != NULL && (!(*outputItem == *recipeRegistry[recipeFilter][selectedRecipe]->getResult()) || outputItem->getSpace() < recipeRegistry[recipeFilter][selectedRecipe]->getResult()->getAmount())) {
		craftValid = false;
	}

	if (craftValid) {
		craftingTicks++;
		if (craftingTicks >= recipeRegistry[recipeFilter][selectedRecipe]->getTime()) {
			for (int i = 0; i < maxIngredients; i++) {
				if (recipeRegistry[recipeFilter][selectedRecipe]->getIngredients()[i] == NULL) {
					break;
				}
				inputItems[i]->take(recipeRegistry[recipeFilter][selectedRecipe]->getIngredients()[i]->getAmount());
			}
			if (outputItem == NULL) {
				outputItem = new ItemStack(*recipeRegistry[recipeFilter][selectedRecipe]->getResult());
				craftingTicks = 0;
			}
			else {
				outputItem->addStrict(recipeRegistry[recipeFilter][selectedRecipe]->getResult()->getAmount());
				craftingTicks = 0;
			}
		}
	}
	else {
		craftingTicks = 0;
	}
}

ItemStack* Crafter::extractItem() {
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

void Crafter::renderInventory(SDL_Renderer* renderer, float x, float y, float mouseX, float mouseY) {
	float rx = mouseX - x;
	float ry = mouseY - y;
	if (state == STATE_A_RECIPECHOOSE) {
		drawUIBackground(renderer, x, y, 224, 256);
		SDL_SetRenderDrawColor(renderer, 36, 34, 52, 255);
		SDL_FRect recipesArea = { x + 8, y + 8, 208, 240 };
		SDL_RenderFillRect(renderer, &recipesArea);
		int drawnIndex = 0;
		for (int i = 0; i < numRecipes[recipeFilter]; i++) {
			int _x = x + 16 + (drawnIndex % 5) * 40;
			int _y = y + 16 + (drawnIndex / 5) * 40;
			if (recipeRegistry[recipeFilter][i]->getIngredients()[maxIngredients] == NULL) {
				drawUIBackground(renderer, _x, _y, 32, 32);
				recipeRegistry[recipeFilter][i]->getResult()->draw(renderer, _x, _y, 2);
				drawnIndex++;
			}
		}
		int hoveredRecipe = -1;
		if (rx > 16 && rx < 200 && ry > 16 && ry < 232) {
			int recipeNum = SDL_floorf((rx - 16) / 40) + 5 * SDL_floorf((ry - 16) / 40);
			int validIndex = 0;
			for (int i = 0; i < numRecipes[recipeFilter]; i++) {
				if (recipeRegistry[recipeFilter][i]->getIngredients()[maxIngredients] == NULL) {
					if (validIndex == recipeNum) {
						SDL_FRect cursorIcon = { SPRITE_SIZE * 3, 0, SPRITE_SIZE, SPRITE_SIZE };
						SDL_FRect drawPos = { x + 16 + (validIndex % 5) * 40, y + 16 + validIndex / 5 * 40, 32, 32 };
						SDL_RenderTexture(renderer, textureList[TEX_UI], &cursorIcon, &drawPos);
						recipeRegistry[recipeFilter][i]->drawRecipeInfo(renderer, mouseX, mouseY + 24);
						break;
					}
					validIndex++;
				}
			}
		}

		

	}
	else if (state == STATE_A_CRAFT) {
		drawUIBackground(renderer, x, y, 224, 192);

		recipeRegistry[recipeFilter][selectedRecipe]->getResult()->draw(renderer, x + 8, y + 8, 2);


		SDL_FRect srcRect = { SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE };
		SDL_FRect dstRect = { x + 16, y + 32, SPRITE_SIZE * UI_SCALE, SPRITE_SIZE * UI_SCALE };
		for (int i = 0; recipeRegistry[recipeFilter][selectedRecipe]->getIngredients()[i] != NULL; i++) {
			dstRect = { x + 16 + 32 * i, y + 64, SPRITE_SIZE * UI_SCALE, SPRITE_SIZE * UI_SCALE };
			SDL_RenderTexture(renderer, textureList[TEX_UI], &srcRect, &dstRect);
			if (inputItems[i] != NULL) { inputItems[i]->draw(renderer, x + 16 + 32 * i, y + 64, 2); }
		}


		SDL_SetRenderDrawColor(renderer, 51, 57, 65, 255);
		dstRect = { x + 16, y + 96, 160, 4 };
		SDL_RenderFillRect(renderer, &dstRect);
		SDL_SetRenderDrawColor(renderer, 180, 32, 42, 255);
		dstRect = { x + 16, y + 96, 160.0f * ((float)craftingTicks / (float)recipeRegistry[recipeFilter][selectedRecipe]->getTime()), 4 };
		SDL_RenderFillRect(renderer, &dstRect);

		dstRect = { x + 144, y + 64, SPRITE_SIZE * UI_SCALE, SPRITE_SIZE * UI_SCALE };
		SDL_RenderTexture(renderer, textureList[TEX_UI], &srcRect, &dstRect);
		if (outputItem != NULL) { outputItem->draw(renderer, x + 144, y + 64, 2); }


		srcRect = { SPRITE_SIZE * 3, 0, SPRITE_SIZE, SPRITE_SIZE };
		for (int i = 0; i < maxIngredients; i++) {
			if (recipeRegistry[recipeFilter][selectedRecipe]->getIngredients()[i] == NULL) {
				break;
			}
			if (rx > 16 + 32 * i && rx < 48 + 32 * i && ry > 64 && ry < 96) {
				dstRect = { x + 16 + 32 * i, y + 64, SPRITE_SIZE * UI_SCALE, SPRITE_SIZE * UI_SCALE };
				SDL_RenderTexture(renderer, textureList[TEX_UI], &srcRect, &dstRect);
				if (inputItems[i] != NULL && !inputItems[i]->isNull()) {
					drawTextString(renderer, mouseX, mouseY + 24, inputItems[i]->type->name, 32);
				}
			}
		}

		if (rx > 144 && rx < 176 && ry > 64 && ry < 96) {
			dstRect = { x + 144, y + 64, SPRITE_SIZE * UI_SCALE, SPRITE_SIZE * UI_SCALE };
			SDL_RenderTexture(renderer, textureList[TEX_UI], &srcRect, &dstRect);
			if (outputItem != NULL && !outputItem->isNull()) {
				drawTextString(renderer, mouseX, mouseY + 24, outputItem->type->name, 32);
			}

		}



		if (rx > 8 && rx < 40 && ry > 8 && ry < 40) {
			recipeRegistry[recipeFilter][selectedRecipe]->drawRecipeInfo(renderer, mouseX, mouseY + 24);
		}

	}
}


void Crafter::clickInventory(UIElement* playerHotbar, UIElement* playerInventory, ItemStack* cursorItem, float x, float y, float mouseX, float mouseY) {
	float rx = mouseX - x;
	float ry = mouseY - y;
	if (state == STATE_A_RECIPECHOOSE) {
		if (rx > 16 && rx < 200 && ry > 16 && ry < 232) {
			int recipeNum = SDL_floorf((rx - 16) / 40) + 5 * SDL_floorf((ry - 16) / 40);
			int validIndex = 0;
			for (int i = 0; i < numRecipes[recipeFilter]; i++) {
				if (recipeRegistry[recipeFilter][i]->getIngredients()[maxIngredients] == NULL) {
					if (validIndex == recipeNum) {
						selectedRecipe = i;
						state = STATE_A_CRAFT;
					}
					validIndex++;
				}
			}
		}

	}
	else if (state == STATE_A_CRAFT) {
		if (rx > 8 && rx < 40 && ry > 8 && ry < 40) {
			state = STATE_A_RECIPECHOOSE;
		}

		for (int i = 0; i < maxIngredients; i++) {
			if (recipeRegistry[recipeFilter][selectedRecipe]->getIngredients()[i] == NULL) {
				break;
			}
			if (rx > 16 + 32 * i && rx < 48 + 32 * i && ry > 64 && ry < 96) {
				if (*recipeRegistry[recipeFilter][selectedRecipe]->getIngredients()[i] == *cursorItem || cursorItem->isNull()) {
					if (inputItems[i] != NULL && !cursorItem->isNull() && *cursorItem == *inputItems[i]) {
						cursorItem->take(inputItems[i]->add(cursorItem->getAmount()));
					}
					else {
						ItemStack* temp = new ItemStack(*cursorItem);
						cursorItem->take(cursorItem->getAmount());
						if (inputItems[i] != NULL) {
							cursorItem->add(inputItems[i]->getAmount(), inputItems[i]->type);
						}
						inputItems[i] = temp;
					}
				}
			}
		}

		if (rx > 144 && rx < 176 && ry > 64 && ry < 96) {
			if (outputItem != NULL && !cursorItem->isNull() && *outputItem == *cursorItem) {
				outputItem->take(cursorItem->add(outputItem->getAmount()));
				if (outputItem->getAmount() == 0) {
					outputItem = NULL;
				}
			}
			else if (outputItem != NULL && cursorItem->isNull()) {
				cursorItem->add(outputItem->getAmount(), outputItem->type);
				outputItem = NULL;
			}

		}
	}

};

bool Crafter::acceptItem(ItemStack* item, int x, int y, Direction direction, bool forced) {
	if (!forced) {
		return false;
	}

	for (int i = 0; i < maxIngredients; i++) {
		if (*recipeRegistry[recipeFilter][selectedRecipe]->getIngredients()[i] == *item) {
			inputItems[i]->type = item->type;
			return inputItems[i]->addStrict(item->getAmount());
		}
	}
	return false;
}

void Crafter::DrawPreview(SDL_Renderer* renderer, float _x, float _y, Direction _direction) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);

	SDL_FRect tileRect = { _x, _y, TILE_SIZE*2, TILE_SIZE*2};
	SDL_FRect texRect = { SPRITE_SIZE * 2, 0, SPRITE_SIZE*2, SPRITE_SIZE*2 };

	SDL_SetTextureAlphaMod(textureList[TEX_TILES1], 128);
	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);
	SDL_SetTextureAlphaMod(textureList[TEX_TILES1], 255);
}