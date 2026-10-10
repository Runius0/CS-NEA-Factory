#include "resourceGenerators.h"

Generator::Generator(Item* generationItem) : Machine() {
	width = 1;
	height = 1;
	itemType = generationItem;
	solid = true;
	usesItems = true;
};

void Generator::draw(SDL_Renderer* renderer, float _x, float _y) {

	SDL_FRect tileRect = { _x, _y, TILE_SIZE, TILE_SIZE };
	SDL_FRect texRect = { SPRITE_SIZE * 5, SPRITE_SIZE * 3, SPRITE_SIZE, SPRITE_SIZE };
	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);

}

ItemStack* Generator::extractItem() {

	if (Cooldown) {
		return NULL;
	}
	Cooldown = maxCooldown;
	return new ItemStack(itemType, 1);
}

void Generator::tick(World* world, int gameTick) {
	if (Cooldown) { Cooldown--; }
};


void Generator::DrawPreview(SDL_Renderer* renderer, float _x, float _y, Direction _direction) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);

	SDL_FRect tileRect = { _x, _y, TILE_SIZE, TILE_SIZE };
	SDL_FRect texRect = { SPRITE_SIZE * 5, SPRITE_SIZE * 3, SPRITE_SIZE, SPRITE_SIZE };

	SDL_SetTextureAlphaMod(textureList[TEX_TILES1], 128);
	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);
	SDL_SetTextureAlphaMod(textureList[TEX_TILES1], 255);
}

TinGenerator::TinGenerator() : Generator(ITEM[8]) {
}

Machine* TinGenerator::copy(int _worldX, int _worldY, Direction direction) {

	Machine* out = new TinGenerator();
	out->init(_worldX, _worldY, direction);
	out->ID = ID;
	return out;
}