#include "caveGen.h"

// TODO: function that randomly picks a room to generate


const char* getRoomString() {
	switch (SDL_rand(3))
	{
	case 0:
		return "content/rooms/corridorS.crm";
	case 1:
		return "content/rooms/bendL.crm";
	case 2:
		return "content/rooms/bendR.crm";
	default:
		return "content/rooms/corridorS.crm";
	} 
}

// note: rooms generate upwards by default
void getCoords(int x, int y, Direction dir, int* out_x, int* out_y) {
	switch (dir)
	{
	case Right:
		*out_x = -y;
		*out_y = x;
		return;
	case Down:
		*out_x = -x;
		*out_y = -y;
		return;
	case Left:
		*out_x = y;
		*out_y = -x;
		return;
	case Up:
		*out_x = x;
		*out_y = y;
		return;
	}
}

void generateRoom(int depth, int _x, int _y, Direction dir, SDL_IOStream* file, CaveWorld* world) {
	if (depth > 4) { return; }

	Uint8 width, height;
	int startX = _x;
	int startY = _y;
	SDL_ReadU8(file, &width);
	SDL_ReadU8(file, &height);
	Uint8 offset = 0;
	SDL_ReadU8(file, &offset);
	switch (dir)
	{
	case Right:
		startY -= offset;
		break;
	case Down:
		startX += offset;
		break;
	case Left:
		startY += offset;
		break;
	case Up:
		startX -= offset;
		break;
	}
	int offX, offY;
	Uint8 tileType;
	for (int y = 1 - height; y <= 0; y++) {
		for (int x = 0; x < width; x++) {
			getCoords(x, y, dir, &offX, &offY);
			SDL_ReadU8(file, &tileType);
			switch (tileType)
			{
			case 0:
				world->setTile(new CaveWall(startX + offX, startY + offY), startX + offX, startY + offY);
				break;
			case 1:
				world->setTile(new CaveDirt(startX + offX, startY + offY), startX + offX, startY + offY);
				break;
			default:
				break;
			}
		}
	}

	// top left coords of room
	int x = 0;
	int y = 0;
	switch (dir)
	{
	case Right:
		x = _x + 1;
		y = _y - offset;
		break;
	case Down:
		x = _x - offset;
		y = _y;
		break;
	case Left:
		x = _x - width;
		y = _y - offset + 1;
		break;
	case Up:
		x = _x - offset;
		y = _y - height + 1;
		break;
	}

	Uint8 specialX, specialY, specialType;
	SDL_ReadU8(file, &specialX);
	SDL_ReadU8(file, &specialY);
	SDL_ReadU8(file, &specialType);
	while (!(specialX == 0 && specialY == 0 && specialType == 0)) {
		// spawn specials
	}

	Uint8 exitDirection, exitOffset;
	SDL_ReadU8(file, &exitDirection);
	SDL_ReadU8(file, &exitOffset);



	while (!(exitDirection == 0 && exitOffset == 0)) {
		switch ((exitDirection + dir - Up + 4) % 4)
		{
		case 0: // up
			//generateRoom(depth + 1, x + exitOffset, y-1, Up, SDL_IOFromFile(getRoomString(), "r"), world);
			break;
		case 1: // right
			generateRoom(depth + 1, x + width + 2, y + exitOffset, Right, SDL_IOFromFile(getRoomString(), "r"), world);
			break;
		case 2: // down
			generateRoom(depth + 1, x + exitOffset, y + height, Down, SDL_IOFromFile(getRoomString(), "r"), world);
			break;
		case 3: // left
			generateRoom(depth + 1, x-1, y + exitOffset, Left, SDL_IOFromFile(getRoomString(), "r"), world);
			break;
		}
		SDL_ReadU8(file, &exitDirection);
		SDL_ReadU8(file, &exitOffset);
	}


	SDL_CloseIO(file);
}

void generateCaves(CaveWorld* world, Machine* platform) {
	SDL_IOStream* startRoom = SDL_IOFromFile("content/rooms/special/start.crm", "r");
	SDL_Log(SDL_GetError());
	generateRoom(0, 8, 11, Up, startRoom, world);
	platform->place(world);
};