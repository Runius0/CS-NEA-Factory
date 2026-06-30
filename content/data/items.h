#pragma once
#include "../../src/core/machineItem.h"

extern Item* ITEM[256];

void registerItem(Item* item);

// fuck it hardcode this shit or load it from a JSON no need to split out into files like the machines
void loadItems();