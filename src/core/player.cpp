#include "player.h"

Player::Player() {
	x = 0;
	y = 0;
	animationTimer = FRAME_LENGTH;
	animationFrame = 0;
	animation = idle;
	direction = Down;
}

void Player::draw(SDL_Renderer* renderer) {
	animationTimer--;
	if (animationTimer <= 0) {
		animationTimer = FRAME_LENGTH;
		animationFrame++;
	}
	animationFrame = animationFrame % animationLengths[animation];

	SDL_FRect screenRect = { SCREEN_WIDTH / 2 - TILE_SIZE/2, SCREEN_HEIGHT / 2 - TILE_SIZE/2, TILE_SIZE, TILE_SIZE};
	SDL_FRect imageRect = { direction * SPRITE_SIZE + animationFrame * SPRITE_SIZE * 4, animation * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE };

	SDL_RenderTexture(renderer, textureList[TEX_PLAYER], &imageRect, &screenRect);
}

void Player::movement(const bool* keyboard) {
	// get movement on each axis
	int HorizontalInput = (int)keyboard[SDL_SCANCODE_D] - (int)keyboard[SDL_SCANCODE_A];
	int VerticalInput = (int)keyboard[SDL_SCANCODE_S] - (int)keyboard[SDL_SCANCODE_W];
	bool hasMoved = false;

	if (HorizontalInput == 1) {
		x += 1;
		direction = Right;
		hasMoved = true;
	}
	else if (HorizontalInput == -1) {
		x -= 1;
		direction = Left;
		hasMoved = true;
	}

	if (VerticalInput == 1) {
		y += 1;
		direction = Down;
		hasMoved = true;
	}
	else if (VerticalInput == -1) {
		y -= 1;
		direction = Up;
		hasMoved = true;
	}

	if (hasMoved) {
		animation = walk;
	}
	else {
		animation = idle;
	}
}

float Player::getX() {
	return x;
}
float Player::getY() {
	return y;
}