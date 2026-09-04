#pragma once
#include "../../../src/core/machine.h"
#include "../../../src/core/item.h"
#include "../../../src/core/recipe.h"

class Furnace : public Machine {
	int craftingTicks = 0;
	ItemStack* inputItem;
	ItemStack* outputItem;
	Recipe* currentRecipe;
public:
	Furnace(int worldX, int worldY, Direction direction);
	void draw(SDL_Renderer* renderer, float x, float y) override;
	static void DrawPreview(SDL_Renderer* renderer, float x, float y, Direction direction);
	bool acceptItem(ItemStack* item, int x, int y, Direction direction, bool forced) override;
	ItemStack* extractItem() override;

	void tick(World* world, int gameTick) override;
	bool interract() override { return true; }
	void renderInventory(SDL_Renderer* renderer, float x, float y, float mouseX, float mouseY) override;
	void clickInventory(UIElement* playerHotbar, UIElement* playerInventory, ItemStack** cursorItem, float x, float y, float mouseX, float mouseY) override;
};