#include "machineItem.h"


MachineItem::MachineItem(MACHINE_ID _machine, char* _name, SDL_FRect _sprite, int _maxStack) : Item(_name, _sprite, _maxStack) {
	machine = _machine;
	placeable = true;
}

Machine* MachineItem::getNew(int x, int y, Direction direction) {
	return NewMachine(machine, x, y, direction);
}

void MachineItem::drawPreview(SDL_Renderer* renderer, float x, float y, Direction direction) {
	DrawMachinePreview(machine, renderer, x, y, direction);
};

bool MachineItem::interact(World* world, int worldX, int worldY, int* stackSize, Player* playerInfo) {
	if (MACHINE[machine]->canPlace(world, worldX, worldY, playerInfo->placingDirection)) {
		Machine* placed = NewMachine(machine, worldX, worldY, playerInfo->placingDirection);
		placed->itemID = ID;
		placed->place(world);
		(*stackSize)--;
		return true;
	}
	else {
		return false;
	}
}