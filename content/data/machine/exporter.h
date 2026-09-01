#pragma once
#include "conveyor.h"

class Exporter : public Conveyor {
	int frame = 0;
	public:
		Exporter(int worldX, int worldY, Direction direction);
		void draw(SDL_Renderer* renderer, float x, float y) override;
		void tick(World* world, int gameTick) override;
		static void DrawPreview(SDL_Renderer* renderer, float x, float y, Direction direction);
};