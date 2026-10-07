#pragma once
#include "../../core.h"

// needed for tile size const, so we can size and place player correctly
#include "tile.h"
#include "world.h"

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
const float FRAME_LENGTH = 3;

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
		float animationTimer;
		void draw(SDL_Renderer* renderer);
		void movement(const bool* keyboardState, float deltaTick, World* world);
		void setAnimation(AnimationState anim);
		void setPos(int X, int Y);
		void setState(PlayerState state);
		float getX();
		float getY();
};