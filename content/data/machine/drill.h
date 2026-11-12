#pragma once
#include "../../../src/core/machine.h"
#include "../../../src/core/item.h"
#include "../../../src/caves/oreRock.h"

class drill : public Machine {
	protected:
		int frame = 0;
		signed char drill_progress = 0;
		Item* item_type;
		int oreCount = 0;

		int targetX, targetY;

	public:
		drill();
		void init(int worldX, int worldY, Direction direction);
		Machine* copy(int worldX, int worldY, Direction direction);
		void draw(SDL_Renderer* renderer, float x, float y) override;
		void tick(World* world, int gameTick) override;
		ItemStack* extractItem();
		void DrawPreview(SDL_Renderer* renderer, float x, float y, Direction direction);
};