#pragma once
#include "../../../src/core/machine.h"
#include "../../../src/core/item.h"

class SurfacePlatform : public Machine {
public:
	SurfacePlatform();
	void init(int worldX, int worldY, Direction direction);
	Machine* copy(int worldX, int worldY, Direction direction);
	void draw(SDL_Renderer* renderer, float x, float y) override;
	void DrawPreview(SDL_Renderer* renderer, float x, float y, Direction direction);

	bool interract(Player* player) override;
};