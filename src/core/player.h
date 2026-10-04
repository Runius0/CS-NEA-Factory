#pragma once
#include "../../core.h"

// needed for tile size const, so we can size and place player correctly
#include "tile.h"

enum AnimationState {
	idle,
	walk,
	descend
};

const int animationLengths[] = {1, 4, 10};
const int FRAME_LENGTH = 64;

class Player {
	float x;
	float y;
	bool actionable;
	public:
		Player();
		Direction direction;
		Direction placingDirection;
		AnimationState animation;
		int animationFrame;
		int animationTimer;
		void draw(SDL_Renderer* renderer);
		void movement(const bool* keyboardState);
		void setAnimation(AnimationState anim);
		float getX();
		float getY();
};