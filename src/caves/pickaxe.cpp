#include "pickaxe.h"


Pickaxe::Pickaxe(float _maxCooldown, char* _name, SDL_FRect _sprite, int _maxStack) : Item(_name, _sprite, _maxStack) {
	maxCooldown = _maxCooldown;
	cooldown = 0;
	needsTicking = true;
}

void Pickaxe::tick(float deltaTick, Player* holder) {
	cooldown -= deltaTick;
	if (cooldown < 0) {
		cooldown = 0;
	}
}

bool Pickaxe::interact(World* world, int worldX, int worldY, int* stackSize, Player* playerInfo, Item** result) {
	if (cooldown == 0) {
		Tile* tile = world->getTile(worldX, worldY);
		if (tile->flags & T_ISORE) {
			// convert tile* to oreRock*
			// add resultant ore to player inventory
			OreRock* oreTile = (OreRock*) tile;
			*result = oreTile->type;
			cooldown = maxCooldown;
		}
	}
	return false;
}