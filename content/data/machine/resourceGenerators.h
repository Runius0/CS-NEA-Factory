#pragma once
#include "../../../src/core/machine.h"
#include "../../../src/core/item.h"

class Generator : public Machine {
	Item* itemType;
	int maxCooldown = 20;
	int Cooldown = 20;
public:
	Generator(Item* generationItem);
	void draw(SDL_Renderer* renderer, float x, float y) override;
	void tick(World* world, int gameTick) override;
	void DrawPreview(SDL_Renderer* renderer, float x, float y, Direction direction);
	ItemStack* extractItem() override;
};

class TinGenerator : public Generator {
	public:
		TinGenerator();
		Machine* copy(int worldX, int worldY, Direction direction);
};