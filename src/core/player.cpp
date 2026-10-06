#include "player.h"

Player::Player() {
	x = 0;
	y = 0;
	animationTimer = FRAME_LENGTH;
	animationFrame = 0;
	animation = a_idle;
	direction = Down;
	placingDirection = Right;
	actionable = true;
}

void Player::draw(SDL_Renderer* renderer) {
	stateTimer++;
	animationTimer--;
	if (animationTimer <= 0) {
		animationTimer = FRAME_LENGTH;
		animationFrame++;
	}
	if (animationFrame >= animationLengths[animation]) {
		animationFrame -= animationLengths[animation];
		actionable = true;
	}

	SDL_FRect screenRect = { SCREEN_WIDTH / 2 - TILE_SIZE/2, SCREEN_HEIGHT / 2 - TILE_SIZE/2, TILE_SIZE, TILE_SIZE};
	SDL_FRect imageRect = { direction * SPRITE_SIZE + animationFrame * SPRITE_SIZE * 4, animation * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE };

	SDL_RenderTexture(renderer, textureList[TEX_PLAYER], &imageRect, &screenRect);
}

void Player::setAnimation(AnimationState anim) {
	animationTimer = FRAME_LENGTH;
	animationFrame = 0;
	animation = anim;
	actionable = false;
}

void Player::setPos(int _x, int _y) {
	x = _x;
	y = _y;
}

void Player::setState(PlayerState _state) {
	state = _state;
	stateTimer = 0;
}
void Player::movement(const bool* keyboard) {
	if (!actionable) { return; }
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
		animation = a_walk;
	}
	else {
		animation = a_idle;
	}

}

float Player::getX() {
	return x;
}
float Player::getY() {
	return y;
}