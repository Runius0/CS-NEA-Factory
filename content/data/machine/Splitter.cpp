#include "splitter.h"

Splitter::Splitter(int _worldX, int _worldY, Direction direction) : Conveyor(_worldX, _worldY, direction) {
	width = 1;
	height = 1;

	switch (direction)
	{
	case Right:
		targetX_2 = _worldX + 1;
		targetY_2 = _worldY + 1;
		height = 2;
		break;
	case Down:
		targetX_2 = _worldX + 1;
		targetY_2 = _worldY + 1;
		width = 2;
		break;
	case Left:
		targetX_2 = _worldX - 1;
		targetY_2 = _worldY + 1;
		height = 2;
		break;
	case Up:
		targetX_2 = _worldX + 1;
		targetY_2 = _worldY - 1;
		width = 2;
		break;
	}
};

void Splitter::draw(SDL_Renderer* renderer, float _x, float _y) {

	SDL_FRect tileRect = { _x, _y, TILE_SIZE, TILE_SIZE };
	if (width == 2) {
		tileRect.w = TILE_SIZE * 2;
	}
	else {
		tileRect.h = TILE_SIZE * 2;
	}
	SDL_FRect texRect = { frame * SPRITE_SIZE, SPRITE_SIZE * 8 + SPRITE_SIZE * direction, SPRITE_SIZE, SPRITE_SIZE };
	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);
}

void Splitter::drawOverlay(SDL_Renderer* renderer, float _x, float _y) {
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
			item2_type->draw(renderer, x + TILE_SIZE / 2 - item2_progress, y);
			break;
		case Up:
			item2_type->draw(renderer, x, y + TILE_SIZE / 2 - item2_progress);
			break;
		}
	}
	if (width == 2) {
		x = _x + 5 * TILE_SIZE / 4;
	}
	else {
		y = _y + 5 * TILE_SIZE / 4;
	}
	if (item1_progress_2 != 64) {
		switch (direction)
		{
		case Right:
			item1_type_2->draw(renderer, x + item1_progress_2, y);
			break;
		case Down:
			item1_type_2->draw(renderer, x, y + item1_progress_2);
			break;
		case Left:
			item1_type_2->draw(renderer, x - item1_progress_2, y);
			break;
		case Up:
			item1_type_2->draw(renderer, x, y - item1_progress_2);
			break;
		}
	}
	if (item2_progress_2 != 64) {
		switch (item2_direction)
		{
		case Right:
			item2_type_2->draw(renderer, x - TILE_SIZE / 2 + item2_progress_2, y);
			break;
		case Down:
			item2_type_2->draw(renderer, x, y - TILE_SIZE / 2 + item2_progress_2);
			break;
		case Left:
			item2_type_2->draw(renderer, x + TILE_SIZE / 2 - item2_progress_2, y);
			break;
		case Up:
			item2_type_2->draw(renderer, x, y + TILE_SIZE / 2 - item2_progress_2);
			break;
		}
	}
}


void Splitter::tick(World* world, int gameTick) {
	frame = gameTick % 4;


	if (item1_progress < 16) {
		item1_progress += 2;
	}
	if (item2_progress < 16) {
		item2_progress += 2;
	}
	if (item1_progress_2 < 16) {
		item1_progress_2 += 2;
	}
	if (item2_progress_2 < 16) {
		item2_progress_2 += 2;
	}
	if (item2_progress == 16) {
		if (lane1_switch) {
			if (item1_progress_2 == 64) {
				item1_progress_2 = 0;
				item1_type_2 = item2_type;
				item2_progress = 64;
				lane1_switch = false;
			}
			else if ((item1_progress_2 == 16) && (item1_progress == 64)) {
				item1_progress = 0;
				item1_type = item2_type;
				item2_progress = 64;
			}
		}
		else {
			if (item1_progress == 64) {
				item1_progress = 0;
				item1_type = item2_type;
				item2_progress = 64;
				lane1_switch = true;
			}
			else if ((item1_progress == 16) && (item1_progress_2 == 64)) {
				item1_progress_2 = 0;
				item1_type_2 = item2_type;
				item2_progress = 64;
			}
		}
	}
	if (item2_progress_2 == 16) {
		if (lane2_switch) {
			if (item1_progress == 64) {
				item1_progress = 0;
				item1_type = item2_type_2;
				item2_progress_2 = 64;
				lane2_switch = false;
			}
			else if ((item1_progress == 16 || item1_progress == 0) && (item1_progress_2 == 64)) {
				item1_progress_2 = 0;
				item1_type_2 = item2_type_2;
				item2_progress_2 = 64;
			}
		}
		else {
			if (item1_progress_2 == 64) {
				item1_progress_2 = 0;
				item1_type_2 = item2_type_2;
				item2_progress_2 = 64;
				lane2_switch = true;
			}
			else if ((item1_progress_2 == 16 || item1_progress_2 == 0) && (item1_progress == 64)) {
				item1_progress = 0;
				item1_type = item2_type_2;
				item2_progress_2 = 64;
			}
		}
	}

	if (item1_progress == 16) {
		Tile* targetTile = world->getTile(targetX, targetY);
		if (targetTile->solid) {
			if (((Machine*)targetTile)->acceptItem(new ItemStack(item1_type, 1), targetX, targetY, direction, false)) {
				item1_progress = 64;
			};
		}
	}
	if (item1_progress_2 == 16) {
		Tile* targetTile = world->getTile(targetX_2, targetY_2);
		if (targetTile->solid) {
			if (((Machine*)targetTile)->acceptItem(new ItemStack(item1_type_2, 1), targetX_2, targetY_2, direction, false)) {
				item1_progress_2 = 64;
			};
		}
	}
}


bool Splitter::acceptItem(ItemStack* item, int x, int y, Direction direction, bool forced) {
	if (x != worldX || y != worldY) {
		if (item->getAmount() != 1 || item2_progress_2 != 64) {
			return false;
		}
		item2_progress_2 = 0;
		item2_type_2 = item->type;
		item2_direction_2 = direction;
		return true;
	}
	if (item->getAmount() != 1 || item2_progress != 64) {
		return false;
	}
	item2_progress = 0;
	item2_type = item->type;
	item2_direction = direction;
	return true;
}

void Splitter::DrawPreview(SDL_Renderer* renderer, float _x, float _y, Direction _direction) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);

	SDL_FRect tileRect = { _x, _y, TILE_SIZE, TILE_SIZE };
	SDL_FRect texRect = { 0, SPRITE_SIZE * 8 + SPRITE_SIZE * _direction, SPRITE_SIZE, SPRITE_SIZE };

	if (_direction % 2 == 1) {
		tileRect.w = TILE_SIZE * 2;
	}
	else {
		tileRect.h = TILE_SIZE * 2;
	}
	SDL_SetTextureAlphaMod(textureList[TEX_TILES1], 128);
	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);
	SDL_SetTextureAlphaMod(textureList[TEX_TILES1], 255);
}