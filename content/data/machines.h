#pragma once
#include "machine/conveyor.h"
#include "machine/importer.h"
#include "machine/exporter.h"

enum MACHINE_ID {
	MACHINE_CONVEYOR,
	MACHINE_IMPORTER,
	MACHINE_EXPORTER
};

void DrawMachinePreview(MACHINE_ID type, SDL_Renderer* renderer, float x, float y, Direction direction);

Machine* NewMachine(MACHINE_ID type, int x, int y, Direction direction);