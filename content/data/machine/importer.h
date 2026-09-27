#pragma once
#include "conveyor.h"

class Importer : public Conveyor {
	protected:
		int extractionX, extractionY;
	public:
		Importer();
		void init(int worldX, int worldY, Direction direction);
		Machine* copy(int worldX, int worldY, Direction direction);
		void draw(SDL_Renderer* renderer, float x, float y) override;
		void tick(World* world, int gameTick) override;
		void DrawPreview(SDL_Renderer* renderer, float x, float y, Direction direction);
};