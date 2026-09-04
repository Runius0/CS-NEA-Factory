#include "resourceGenerators.h"

Generator::Generator(int _worldX, int _worldY, Direction direction, Item* generationItem) : Machine(_worldX, _worldY, direction) {
	width = 1;
	height = 1;
	itemType = generationItem;
};

void Generator::draw(SDL_Renderer* renderer, float _x, float _y) {

	SDL_FRect tileRect = { _x, _y, TILE_SIZE, TILE_SIZE };
	SDL_FRect texRect = { SPRITE_SIZE * 4, SPRITE_SIZE * 4, SPRITE_SIZE, SPRITE_SIZE };
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
	SDL_FRect texRect = { SPRITE_SIZE * 4, SPRITE_SIZE * 4, SPRITE_SIZE, SPRITE_SIZE };

	SDL_SetTextureAlphaMod(textureList[TEX_TILES1], 128);
	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);
	SDL_SetTextureAlphaMod(textureList[TEX_TILES1], 255);
}

TinGenerator::TinGenerator(int _worldX, int _worldY, Direction direction) : Generator(_worldX, _worldY, direction, ITEM[8]) {
	ID = 7;
}