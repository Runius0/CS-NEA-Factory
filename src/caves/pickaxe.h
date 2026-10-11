#pragma once
#include "../core/item.h"
#include "../core/machine.h"

#include "oreRock.h"

class Pickaxe : public Item {
	float cooldown;
	float maxCooldown;

	public:
		Pickaxe(float maxCooldown, char* name, SDL_FRect sprite, int maxStack);
		void tick(float deltaTick, Player* holder);
		bool interact(World* world, int worldX, int worldY, int* stackSize, Player* playerInfo, Item** result) override;
};