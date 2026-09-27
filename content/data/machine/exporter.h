#pragma once
#include "conveyor.h"

class Exporter : public Conveyor {
	int frame = 0;
	public:
		Exporter();
		// no need for init as conveyor handles that
		Machine* copy(int worldX, int worldY, Direction direction);
		void draw(SDL_Renderer* renderer, float x, float y) override;
		void tick(World* world, int gameTick) override;
		void DrawPreview(SDL_Renderer* renderer, float x, float y, Direction direction);
};