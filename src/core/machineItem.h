#pragma once
#include "item.h"
#include "machine.h"

#include "../../content/data/machines.h"

class MachineItem : public Item {
	MACHINE_ID machine;

	public:
		MachineItem(MACHINE_ID machine, char* name, SDL_FRect sprite, int maxStack);
		Machine* getNew(int x, int y, Direction direction);
		void drawPreview(SDL_Renderer* renderer, float x, float y, Direction direction);
};