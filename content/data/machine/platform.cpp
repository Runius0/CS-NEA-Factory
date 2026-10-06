#include "platform.h"

SurfacePlatform::SurfacePlatform() : Machine() {
	width = 4;
	height = 4;
	vel = 0;
	depth = 0;
	targetPlayer = NULL;
	currentState = s_normal;
};

void SurfacePlatform::init(int _worldX, int _worldY, Direction direction) {
	Machine::init(_worldX, _worldY, direction);
};

Machine* SurfacePlatform::copy(int _worldX, int _worldY, Direction _direction) {
	Machine* out = new SurfacePlatform();
	out->init(_worldX, _worldY, _direction);
	out->ID = ID;
	return out;
};

bool SurfacePlatform::interract(Player* player) {
	player->setAnimation(a_hide);
	player->setState(s_descend);
	player->setPos(worldX * TILE_SIZE + 2*TILE_SIZE, worldY * TILE_SIZE + 2 * TILE_SIZE);
	targetPlayer = player;
	currentState = s_descend;
	return false;
}

void SurfacePlatform::tick(World* world, int gameTick) {
	if (currentState == s_descend) {
		vel += 1;
		depth += vel / 2;
	}
}

void SurfacePlatform::draw(SDL_Renderer* renderer, float _x, float _y) {

	SDL_FRect tileRect = { _x, _y + depth, TILE_SIZE * 4, TILE_SIZE * 4 };
	SDL_FRect texRect = { SPRITE_SIZE * 8, SPRITE_SIZE * 5, SPRITE_SIZE * 4, SPRITE_SIZE * 4 };
	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);
	if (currentState == s_descend) {
		tileRect = { _x + TILE_SIZE * 2 - TILE_SIZE/2, _y + TILE_SIZE * 2 - TILE_SIZE / 2 + depth, TILE_SIZE, TILE_SIZE };
		texRect = { SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE };
		SDL_RenderTexture(renderer, textureList[TEX_PLAYER], &texRect, &tileRect);

	}

}

void SurfacePlatform::DrawPreview(SDL_Renderer* renderer, float _x, float _y, Direction _direction) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);

	SDL_FRect tileRect = { _x, _y, TILE_SIZE*4, TILE_SIZE*4 };
	SDL_FRect texRect = { SPRITE_SIZE * 8, SPRITE_SIZE * 5, SPRITE_SIZE * 4, SPRITE_SIZE * 4 };

	SDL_SetTextureAlphaMod(textureList[TEX_TILES1], 128);
	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);
	SDL_SetTextureAlphaMod(textureList[TEX_TILES1], 255);
}

CavesPlatform::CavesPlatform() : Machine() {
	width = 4;
	height = 4;
	vel = 0;
	depth = 0;
	targetPlayer = NULL;
	currentState = s_normal;
};

void CavesPlatform::init(int _worldX, int _worldY, Direction direction) {
	Machine::init(_worldX, _worldY, direction);
};

Machine* CavesPlatform::copy(int _worldX, int _worldY, Direction _direction) {
	Machine* out = new CavesPlatform();
	out->init(_worldX, _worldY, _direction);
	out->ID = ID;
	return out;
};

bool CavesPlatform::interract(Player* player) {
	/*
	player->setAnimation(a_hide);
	player->setState(s_descend);
	player->setPos(worldX * TILE_SIZE + 2 * TILE_SIZE, worldY * TILE_SIZE + 2 * TILE_SIZE);
	targetPlayer = player;
	currentState = s_descend;
	return false;
	*/
	return false;
}

void CavesPlatform::tick(World* world, int gameTick) {
	if (currentState == s_descend_out) {
		vel -= 1;
		depth += vel / 2;
		if (vel <= 9) {
			if (depth < 0) {
				vel = 9;
			}
			else {
				depth = 0;
				currentState = s_normal;
				targetPlayer->setAnimation(a_idle);
				targetPlayer->setState(s_normal);
			}
		}
	}
}

void CavesPlatform::draw(SDL_Renderer* renderer, float _x, float _y) {

	SDL_FRect tileRect = { _x, _y + depth, TILE_SIZE * 4, TILE_SIZE * 4 };
	SDL_FRect texRect = { SPRITE_SIZE * 8, SPRITE_SIZE * 5, SPRITE_SIZE * 4, SPRITE_SIZE * 4 };
	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);

}

void CavesPlatform::drawOverlay(SDL_Renderer* renderer, float _x, float _y) {

	if (currentState == s_descend_out) {
		SDL_FRect tileRect = { _x, _y + depth, TILE_SIZE * 4, TILE_SIZE * 4 };
		SDL_FRect texRect = { SPRITE_SIZE * 8, SPRITE_SIZE * 5, SPRITE_SIZE * 4, SPRITE_SIZE * 4 };
		SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);
		tileRect = { _x + TILE_SIZE * 2 - TILE_SIZE / 2, _y + TILE_SIZE * 2 - TILE_SIZE / 2 + depth, TILE_SIZE, TILE_SIZE };
		texRect = { SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE };
		SDL_RenderTexture(renderer, textureList[TEX_PLAYER], &texRect, &tileRect);

	}

}

void CavesPlatform::DrawPreview(SDL_Renderer* renderer, float _x, float _y, Direction _direction) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);

	SDL_FRect tileRect = { _x, _y, TILE_SIZE * 4, TILE_SIZE * 4 };
	SDL_FRect texRect = { SPRITE_SIZE * 8, SPRITE_SIZE * 5, SPRITE_SIZE * 4, SPRITE_SIZE * 4 };

	SDL_SetTextureAlphaMod(textureList[TEX_TILES1], 128);
	SDL_RenderTexture(renderer, textureList[TEX_TILES1], &texRect, &tileRect);
	SDL_SetTextureAlphaMod(textureList[TEX_TILES1], 255);
}
