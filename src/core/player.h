#pragma once
#include "../../core.h"

// needed for tile size const, so we can size and place player correctly
#include "tile.h"

enum AnimationState {
	a_idle,
	a_walk,
	a_hide
};

enum PlayerState {
	s_normal,
	s_ascend,
	s_descend,
	s_ascend_out,
	s_descend_out
};

const int animationLengths[] = {1, 4, 500};
const int FRAME_LENGTH = 64;

class Player {
	float x;
	float y;
	public:
		PlayerState state;
		float stateTimer;
		bool actionable;
		Player();
		Direction direction;
		Direction placingDirection;
		AnimationState animation;
		int animationFrame;
		int animationTimer;
		void draw(SDL_Renderer* renderer);
		void movement(const bool* keyboardState);
		void setAnimation(AnimationState anim);
		void setPos(int X, int Y);
		void setState(PlayerState state);
		float getX();
		float getY();
};