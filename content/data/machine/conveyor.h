#pragma once
#include "../../../src/core/machine.h"

class Conveyor : public Machine {
	int frame = 0;
	int frameTimer = 0;
	public:
		Conveyor(int worldX, int worldY);
		void draw(SDL_Renderer* renderer, float x, float y) override;
		static void DrawPreview(SDL_Renderer* renderer, float x, float y);
};