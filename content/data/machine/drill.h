#pragma once
#include "../../../src/core/machine.h"
#include "../../../src/core/item.h"
#include "../../../src/caves/oreRock.h"

class drill : public Machine {
	protected:
		int frame = 0;
		signed char drill_progress = 0;
		ItemStack* oreItem;

		int targetX, targetY;

	public:
		drill();
		void init(int worldX, int worldY, Direction direction) override;
		Machine* copy(int worldX, int worldY, Direction direction);
		void draw(SDL_Renderer* renderer, float x, float y) override;
		void tick(World* world, int gameTick) override;
		ItemStack* extractItem();
		void DrawPreview(SDL_Renderer* renderer, float x, float y, Direction direction);

		bool interract(Player* player) override { return true; }
		void renderInventory(SDL_Renderer* renderer, float x, float y, float mouseX, float mouseY) override;
		void clickInventory(UIElement* playerHotbar, UIElement* playerInventory, ItemStack* cursorItem, float x, float y, float mouseX, float mouseY) override;
};