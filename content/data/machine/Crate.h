#pragma once
#include "../../../src/core/machine.h"
#include "../../../src/core/item.h"

class Crate : public Machine {
	int frame = 0;
public:
	Crate(int worldX, int worldY, Direction direction);
	void draw(SDL_Renderer* renderer, float x, float y) override;
	static void DrawPreview(SDL_Renderer* renderer, float x, float y, Direction direction);
	bool acceptItem(ItemStack* item, int x, int y, Direction direction, bool forced) override { return true; };
	ItemStack* extractItem() override;
};