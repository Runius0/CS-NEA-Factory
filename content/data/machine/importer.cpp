#include "importer.h"

Importer::Importer(int _worldX, int _worldY, Direction direction) : Conveyor(_worldX, _worldY, direction) {
	width = 1;
	height = 1;

	switch (direction)
	{
	case Right:
		extractionX = _worldX - 1;
		extractionY = _worldY;
		break;
	case Down:
		extractionX = _worldX;
		extractionY = _worldY - 1;
		break;
	case Left:
		extractionX = _worldX + 1;
		extractionY = _worldY;
		break;
	case Up:
		extractionX = _worldX;
		extractionY = _worldY + 1;
		break;
	}
};

void Importer::draw(SDL_Renderer* renderer, float _x, float _y) {

	SDL_FRect tileRect = { _x, _y, TILE_SIZE, TILE_SIZE };
	SDL_FRect texRect = {frame * SPRITE_SIZE, SPRITE_SIZE * 8 + SPRITE_SIZE * direction, SPRITE_SIZE, SPRITE_SIZE };
	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);

	switch (direction)
	{
	case Right:
		item1_type->draw(renderer, _x + TILE_SIZE / 2 + item1_progress, _y);
		item2_type->draw(renderer, _x + item2_progress, _y);
		break;
	case Down:
		item1_type->draw(renderer, _x, _y + TILE_SIZE / 2 + item1_progress);
		item2_type->draw(renderer, _x, _y + item2_progress);
		break;
	case Left:
		item1_type->draw(renderer, _x + TILE_SIZE / 2 - item1_progress, _y);
		item2_type->draw(renderer, _x + TILE_SIZE + item2_progress, _y);
		break;
	case Up:
		item1_type->draw(renderer, _x, _y + TILE_SIZE / 2 - item1_progress);
		item2_type->draw(renderer, _x, _y + TILE_SIZE + item2_progress);
		break;
	}
}

void Importer::tick(World* world, int gameTick) {
	frame = gameTick % 4;
	if (item1_progress < 8) {
		item1_progress++;
	}
	if (item2_progress < 8) {
		item2_progress++;
	}

	if (item1_progress == 8) {
		Tile* targetTile = world->getTile(targetX, targetY);
		if (targetTile->solid) {
			if (((Machine*)targetTile)->acceptItem(new ItemStack(item1_type, 1), false)) {
				item1_progress = 64;
			};
		}
	}
	if (item2_progress == 8) {
		if (item1_progress == 64) {
			item1_progress = 0;
			item2_progress = 64;
			item1_type = item2_type;
		}
	}
	if (gameTick % 4 == 0 && item2_progress == 64) {
		Tile* targetTile = world->getTile(extractionX, extractionY);
		if (targetTile->solid) {
			ItemStack* newItem = ((Machine*)targetTile)->extractItem();
			if (newItem != NULL) {
				item2_progress = 0;
				item2_type = newItem->type;
			}
		}

	}
}


void Importer::DrawPreview(SDL_Renderer* renderer, float _x, float _y, Direction _direction) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);

	SDL_FRect tileRect = { _x, _y, TILE_SIZE, TILE_SIZE };
	SDL_FRect texRect = { 0, SPRITE_SIZE * 8 + SPRITE_SIZE * _direction, SPRITE_SIZE, SPRITE_SIZE };

	SDL_SetTextureAlphaMod(textureList[TEX_TILES1], 128);
	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);
	SDL_SetTextureAlphaMod(textureList[TEX_TILES1], 255);
}