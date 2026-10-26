#pragma once
#include "../../src/core/machineItem.h"
#include "../../src/caves/pickaxe.h"

enum ITEM {
	IT_CONVEYOR = 1,
	IT_EXPORTER,
	IT_IMPORTER,
	IT_CRATE,
	IT_SPLITTER,
	IT_FURNACE,
	IT_ORE_TIN,
	IT_BLOCK_TIN,
	IT_SHEET_TIN,
	IT_GEAR_TIN,
	IT_PICK_BASIC,
	IT_ORE_COPPER,
	IT_ORE_ZINC,
	IT_BLOCK_COPPER,
	IT_BLOCK_ZINC,
	IT_SHEET_COPPER,
	IT_SHEET_ZINC,
	IT_GEAR_COPPER,
	IT_GEAR_ZINC,
};


void registerItem(Item* item);

// fuck it hardcode this shit or load it from a JSON no need to split out into files like the machines
void loadItems();