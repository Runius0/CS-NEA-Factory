#pragma once
#include "../../../src/core/machine.h"
#include "../../../src/core/item.h"

class Conveyor : public Machine {
	protected:
		int frame = 0;
		signed char item1_progress = 64;
		signed char item2_progress = 64;
		Item* item1_type;
		Item* item2_type;
		int targetX, targetY;
	public:
		Conveyor(int worldX, int worldY, Direction direction);
		void draw(SDL_Renderer* renderer, float x, float y) override;
		void tick(World* world, int gameTick) override;
		bool acceptItem(ItemStack* item, bool forced) override;
		static void DrawPreview(SDL_Renderer* renderer, float x, float y, Direction direction);
};