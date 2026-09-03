#include "items.h"


void registerItem(Item* item) {
	ITEM[item->ID] = item;
}

// fuck it hardcode this shit or load it from a JSON no need to split out into files like the machines
void loadItems() {
	registerItem(new MachineItem(MACHINE_CONVEYOR, (char*)"CONVEYOR", {0, 0, SPRITE_SIZE, SPRITE_SIZE}, 50));
	registerItem(new MachineItem(MACHINE_EXPORTER, (char*)"EXPORTER", { SPRITE_SIZE * 2, 0, SPRITE_SIZE, SPRITE_SIZE }, 50));
	registerItem(new MachineItem(MACHINE_IMPORTER, (char*)"IMPORTER", { SPRITE_SIZE * 1, 0, SPRITE_SIZE, SPRITE_SIZE}, 50));
	registerItem(new MachineItem(MACHINE_CRATE, (char*)"CRATE", { SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE }, 50));
	registerItem(new MachineItem(MACHINE_SPLITTER, (char*)"SPLITTER", { SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE }, 50));
	registerItem(new Item((char*)"RAW TEST", { SPRITE_SIZE * 3, 0, SPRITE_SIZE, SPRITE_SIZE }, 50));
	registerItem(new Item((char*)"COOKED TEST", { SPRITE_SIZE * 4, 0, SPRITE_SIZE, SPRITE_SIZE }, 50));
}