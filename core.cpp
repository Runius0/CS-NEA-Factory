#include "core.h"

SDL_Texture* textureList[TEXTURE_AMOUNT];
SDL_FRect* font[256];


void loadFont() {
	for (int i = 0; i < 26; i++) {
		font[65 + i] = new SDL_FRect{ (float)i * 5, 48.0f, 5.0f, 7.0f };
	}
	for (int i = 0; i < 10; i++) {
		font[48 + i] = new SDL_FRect{ 48.0f + (float)i * 5, 16.0f, 5.0f, 7.0f };
	}
	font[120] = new SDL_FRect{ 48.0f, 23.0f, 5.0f, 7.0f };
	font[46] = new SDL_FRect{ 53.0f, 23.0f, 5.0f, 7.0f };
	font[32] = new SDL_FRect{ 0.0f, 0.0f, 5.0f, 7.0f };
}