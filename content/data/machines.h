#pragma once
#include "machine/conveyor.h"
#include "machine/importer.h"
#include "machine/exporter.h"
#include "machine/Splitter.h"
#include "machine/Crate.h"
#include "machine/furnace.h"

enum MACHINE_ID {
	MACHINE_CONVEYOR,
	MACHINE_IMPORTER,
	MACHINE_EXPORTER,
	MACHINE_SPLITTER,
	MACHINE_CRATE,
	MACHINE_FURNACE
};

void DrawMachinePreview(MACHINE_ID type, SDL_Renderer* renderer, float x, float y, Direction direction);

Machine* NewMachine(MACHINE_ID type, int x, int y, Direction direction);