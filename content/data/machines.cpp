#pragma once
#include "machines.h"


void DrawMachinePreview(MACHINE_ID type, SDL_Renderer* renderer, float x, float y, Direction direction) {
	switch (type)
	{
	case MACHINE_CONVEYOR:
		Conveyor::DrawPreview(renderer, x, y, direction);
		break;
	case MACHINE_IMPORTER:
		Importer::DrawPreview(renderer, x, y, direction);
		break;
	case MACHINE_EXPORTER:
		Exporter::DrawPreview(renderer, x, y, direction);
		break;
	case MACHINE_CRATE:
		Crate::DrawPreview(renderer, x, y, direction);
		break;
	default:
		break;
	}
}

Machine* NewMachine(MACHINE_ID type, int x, int y, Direction direction) {
	switch (type)
	{
	case MACHINE_CONVEYOR:
		return new Conveyor(x, y, direction);
		break;
	case MACHINE_IMPORTER:
		return new Importer(x, y, direction);
		break;
	case MACHINE_EXPORTER:
		return new Exporter(x, y, direction);
		break;
	case MACHINE_CRATE:
		return new Crate(x, y, direction);
		break;
	default:
		return NULL;
		break;
	}

}