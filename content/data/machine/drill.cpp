#include "drill.h"

drill::drill() : Machine() {
	width = 1;
	height = 1;
	flags |= T_USESITEMS;
};

void drill::init(int _worldX, int _worldY, Direction direction) {
	Machine::init(_worldX, _worldY, direction);
	switch (direction)
	{
	case Right:
		targetX = _worldX + 1;
		targetY = _worldY;
		break;
	case Down:
		targetX = _worldX;
		targetY = _worldY + 1;
		break;
	case Left:
		targetX = _worldX - 1;
		targetY = _worldY;
		break;
	case Up:
		targetX = _worldX;
		targetY = _worldY - 1;
		break;
	}

};

Machine* drill::copy(int _worldX, int _worldY, Direction _direction) {
	Machine* out = new drill();
	out->init(_worldX, _worldY, _direction);
	out->ID = ID;
	return out;
};

void drill::draw(SDL_Renderer* renderer, float _x, float _y) {

	SDL_FRect tileRect = { _x, _y, TILE_SIZE, TILE_SIZE };
	SDL_FRect texRect = {frame * SPRITE_SIZE, SPRITE_SIZE * 4 + SPRITE_SIZE * direction, SPRITE_SIZE, SPRITE_SIZE };
	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);

}


void drill::tick(World* world, int gameTick) {
	frame = gameTick % 4;
	drill_progress++;
	if (drill_progress == 64) {
		Tile* targetTile = world->getTile(targetX, targetY);
		if (targetTile->flags & T_ISORE) {
			item_type = ((OreRock*)targetTile)->type;
			if (oreCount < item_type->maxStack) {
				oreCount++;
			}
		}
		drill_progress = 0;
	}
}


ItemStack* drill::extractItem() {
	if (oreCount > 0) {
		oreCount--;
		return new ItemStack(item_type, 1);
	}
};

void drill::DrawPreview(SDL_Renderer* renderer, float _x, float _y, Direction _direction) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);

	SDL_FRect tileRect = { _x, _y, TILE_SIZE, TILE_SIZE };
	SDL_FRect texRect = { 0, SPRITE_SIZE * 4 + SPRITE_SIZE * _direction, SPRITE_SIZE, SPRITE_SIZE };

	SDL_SetTextureAlphaMod(textureList[TEX_TILES1], 128);
	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);
	SDL_SetTextureAlphaMod(textureList[TEX_TILES1], 255);

}