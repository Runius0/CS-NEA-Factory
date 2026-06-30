#pragma once
#include "../../../src/core/machine.h"
#include "../../../src/core/item.h"

class Importer : public Machine {
	int frame = 0;
	public:
		Importer(int worldX, int worldY, Direction direction);
		void draw(SDL_Renderer* renderer, float x, float y) override;
		void tick(int gameTick) override;
		static void DrawPreview(SDL_Renderer* renderer, float x, float y, Direction direction);
};