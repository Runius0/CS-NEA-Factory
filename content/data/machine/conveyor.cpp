#include "conveyor.h"

Conveyor::Conveyor(int _worldX, int _worldY, Direction direction) : Machine(_worldX, _worldY, direction) {
	width = 1;
	height = 1;

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

void Conveyor::draw(SDL_Renderer* renderer, float _x, float _y) {

	SDL_FRect tileRect = { _x, _y, TILE_SIZE, TILE_SIZE };
	SDL_FRect texRect = {frame * SPRITE_SIZE, SPRITE_SIZE * 4 + SPRITE_SIZE * direction, SPRITE_SIZE, SPRITE_SIZE };
	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);

}

void Conveyor::drawOverlay(SDL_Renderer* renderer, float _x, float _y) {

	float x = _x + TILE_SIZE / 4;
	float y = _y + TILE_SIZE / 4;
	if (item1_progress != 64) {
		switch (direction)
		{
		case Right:
			item1_type->draw(renderer, x + item1_progress, y);
			break;
		case Down:
			item1_type->draw(renderer, x, y + item1_progress);
			break;
		case Left:
			item1_type->draw(renderer, x - item1_progress, y);
			break;
		case Up:
			item1_type->draw(renderer, x, y - item1_progress);
			break;
		}
	}
	if (item2_progress != 64) {
		switch (item2_direction)
		{
		case Right:
			item2_type->draw(renderer, x - TILE_SIZE / 2 + item2_progress, y);
			break;
		case Down:
			item2_type->draw(renderer, x, y - TILE_SIZE / 2 + item2_progress);
			break;
		case Left:
			item2_type->draw(renderer, x + TILE_SIZE/2 - item2_progress, y);
			break;
		case Up:
			item2_type->draw(renderer, x, y + TILE_SIZE/2 - item2_progress);
			break;
		}
	}
}

void Conveyor::updateItems(World* world) {
	if (item1_progress < 16) {
		item1_progress+= 2;
	}
	if (item2_progress < 16) {
		item2_progress+= 2;
	}
	if (item2_progress == 16) {
		if (item1_progress == 64) {
			item1_progress = 0;
			item2_progress = 64;
			item1_type = item2_type;
		}
	}

}

void Conveyor::tick(World* world, int gameTick) {
	frame = gameTick % 4;
	updateItems(world);

	if (item1_progress == 16) {
		Tile* targetTile = world->getTile(targetX, targetY);
		if (targetTile->solid) {
			if (((Machine*)targetTile)->acceptItem(new ItemStack(item1_type, 1), targetX, targetY, direction, false)) {
				item1_progress = 64;
			};
		}
	}
}

bool Conveyor::acceptItem(ItemStack* item, int x, int y, Direction direction, bool forced) {
	if (item->getAmount() != 1 || item2_progress != 64) {
		return false;
	}
	item2_progress = 0;
	item2_type = item->type;
	item2_direction = direction;
	return true;
}

void Conveyor::DrawPreview(SDL_Renderer* renderer, float _x, float _y, Direction _direction) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);

	SDL_FRect tileRect = { _x, _y, TILE_SIZE, TILE_SIZE };
	SDL_FRect texRect = { 0, SPRITE_SIZE * 4 + SPRITE_SIZE * _direction, SPRITE_SIZE, SPRITE_SIZE };

	SDL_SetTextureAlphaMod(textureList[TEX_TILES1], 128);
	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);
	SDL_SetTextureAlphaMod(textureList[TEX_TILES1], 255);

}