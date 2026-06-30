#pragma once
#include "../../core.h"

// needed for tile size const, so we can size and place player correctly
#include "tile.h"

enum AnimationState {
	idle,
	walk
};

const int animationLengths[] = {1, 4};
const int FRAME_LENGTH = 64;

class Player {
	float x;
	float y;
	public:
		Player();
		Direction direction;
		Direction placingDirection;
		AnimationState animation;
		int animationFrame;
		int animationTimer;
		void draw(SDL_Renderer* renderer);
		void movement(const bool* keyboardState);
		float getX();
		float getY();
};