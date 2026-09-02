#pragma once
#include "conveyor.h"

class Splitter : public Conveyor {
protected:
	int targetX_2, targetY_2;
	signed char item1_progress_2 = 64;
	signed char item2_progress_2 = 64;
	Item* item1_type_2;
	Item* item2_type_2;
	bool lane1_switch = true;
	bool lane2_switch = true;
	Direction item2_direction_2 = Up;
public:
	Splitter(int worldX, int worldY, Direction direction);
	void draw(SDL_Renderer* renderer, float x, float y) override;
	void drawOverlay(SDL_Renderer* renderer, float x, float y) override;
	void tick(World* world, int gameTick) override;
	static void DrawPreview(SDL_Renderer* renderer, float x, float y, Direction direction);
	bool acceptItem(ItemStack* item, int x, int y, Direction direction, bool forced) override;
};
