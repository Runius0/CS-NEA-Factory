#pragma once
#include "../../src/core/machineItem.h"

const int FIRST_ITEM_ID = 10; // first non-machine item ID

void registerItem(Item* item);

// fuck it hardcode this shit or load it from a JSON no need to split out into files like the machines
void loadItems();