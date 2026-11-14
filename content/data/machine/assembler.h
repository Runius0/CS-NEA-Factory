#pragma once
#include "../../../src/core/machine.h"
#include "../../../src/core/item.h"
#include "../../../src/core/recipe.h"

enum assemblerState {
	STATE_A_RECIPECHOOSE,
	STATE_A_CRAFT,
};


class Crafter : public Machine {
	int craftingTicks = 0;
	ItemStack* inputItems[8];
	ItemStack* outputItem;
	int selectedRecipe = -1;
	int frame = 0;
	assemblerState state = STATE_A_RECIPECHOOSE;
public:
	int maxIngredients;
	RecipeType recipeFilter;

	Crafter();
	Machine* copy(int worldX, int worldY, Direction direction);
	void init(int worldX, int worldY, Direction direction);
	void draw(SDL_Renderer* renderer, float x, float y) override;
	void DrawPreview(SDL_Renderer* renderer, float x, float y, Direction direction);
	bool acceptItem(ItemStack* item, int x, int y, Direction direction, bool forced) override;
	ItemStack* extractItem() override;

	void tick(World* world, int gameTick) override;
	bool interract(Player* player) override { return true; }
	void renderInventory(SDL_Renderer* renderer, float x, float y, float mouseX, float mouseY) override;
	void clickInventory(UIElement* playerHotbar, UIElement* playerInventory, ItemStack* cursorItem, float x, float y, float mouseX, float mouseY) override;
};