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