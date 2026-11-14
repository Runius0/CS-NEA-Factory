#include "drill.h"

drill::drill() : Machine() {
	width = 1;
	height = 1;
	flags |= T_USESITEMS | T_SOLID;
};

void drill::init(int _worldX, int _worldY, Direction direction) {
	Machine::init(_worldX, _worldY, direction);
	oreItem = new ItemStack();
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
	SDL_FRect texRect = { SPRITE_SIZE * 12, SPRITE_SIZE * 5 + SPRITE_SIZE * direction, SPRITE_SIZE, SPRITE_SIZE };

	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);

}


void drill::tick(World* world, int gameTick) {
	frame = gameTick % 4;
	drill_progress++;
	if (drill_progress == 64) {
		Tile* targetTile = world->getTile(targetX, targetY);
		if (targetTile->flags & T_ISORE) {
			oreItem->add(1, ((OreRock*)targetTile)->type);
		}
		drill_progress = 0;
	}
}


ItemStack* drill::extractItem() {
	if (oreItem->getAmount() > 0) {
		oreItem->take(1);
		return new ItemStack(oreItem->type, 1);
	}
};
void drill::renderInventory(SDL_Renderer* renderer, float x, float y, float mouseX, float mouseY) {
	drawUIBackground(renderer, x, y, 96, 96);
	SDL_FRect srcRect = { SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE };
	SDL_FRect dstRect = { x + 32, y + 32, SPRITE_SIZE * UI_SCALE, SPRITE_SIZE * UI_SCALE };
	SDL_RenderTexture(renderer, textureList[TEX_UI], &srcRect, &dstRect);
	if (oreItem != NULL) { oreItem->draw(renderer, x + 32, y + 32, 2); }

	float rx = mouseX - x;
	float ry = mouseY - y;
	srcRect = { SPRITE_SIZE * 3, 0, SPRITE_SIZE, SPRITE_SIZE };
	if (rx > 32 && rx < 64 && ry > 32 && ry < 64) {
		dstRect = { x + 32, y + 32, SPRITE_SIZE * UI_SCALE, SPRITE_SIZE * UI_SCALE };
		SDL_RenderTexture(renderer, textureList[TEX_UI], &srcRect, &dstRect);
		if (oreItem != NULL && !oreItem->isNull()) {
			drawTextString(renderer, mouseX, mouseY + 24, oreItem->type->name, 32);
		}

	}

}


void drill::clickInventory(UIElement* playerHotbar, UIElement* playerInventory, ItemStack* cursorItem, float x, float y, float mouseX, float mouseY) {
	float rx = mouseX - x;
	float ry = mouseY - y;
	if (rx > 32 && rx < 64 && ry > 32 && ry < 64) {
		if (oreItem != NULL && !cursorItem->isNull() && *oreItem == *cursorItem) {
			oreItem->take(cursorItem->add(oreItem->getAmount()));
		}
		else if (cursorItem->isNull()) {
			cursorItem->add(oreItem->getAmount(), oreItem->type);
			oreItem->take(oreItem->getAmount());
		}

	}

};

void drill::DrawPreview(SDL_Renderer* renderer, float _x, float _y, Direction _direction) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);

	SDL_FRect tileRect = { _x, _y, TILE_SIZE, TILE_SIZE };
	SDL_FRect texRect = { SPRITE_SIZE * 12, SPRITE_SIZE * 5 + SPRITE_SIZE * _direction, SPRITE_SIZE, SPRITE_SIZE };

	SDL_SetTextureAlphaMod(textureList[TEX_TILES1], 128);
	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);
	SDL_SetTextureAlphaMod(textureList[TEX_TILES1], 255);

}