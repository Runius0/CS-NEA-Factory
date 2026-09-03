#pragma once
#define SDL_MAIN_USE_CALLBACKS
#define SDL_MAIN_HANDLED  /* use the callbacks instead of main() */
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

const int TEXTURE_AMOUNT = 4;
const int SPRITE_SIZE = 16;
enum TEXTURE
{
	TEX_TILES1,
    TEX_PLAYER,
    TEX_UI,
    TEX_ITEM
};

enum Direction
{
    Right,
    Down,
    Left,
    Up
};

extern SDL_Texture* textureList[TEXTURE_AMOUNT];
static void loadTextures(SDL_Renderer* renderer) {
    char texPath[1024];

    // Graphics set 1
    strcpy_s(texPath, SDL_GetBasePath());
    strcat_s(texPath, "img\\FactoryTiles1.png");
    SDL_IOStream* texIn = SDL_IOFromFile(texPath, "r");
    textureList[TEX_TILES1] = IMG_LoadTexture_IO(renderer, texIn, true);
    SDL_SetTextureScaleMode(textureList[TEX_TILES1], SDL_SCALEMODE_NEAREST);
    if (textureList[TEX_TILES1] != NULL) {
        SDL_Log("LOADED TILES 1");
    }

    // Player spritesheet
    strcpy_s(texPath, SDL_GetBasePath());
    strcat_s(texPath, "img\\player.png");
    texIn = SDL_IOFromFile(texPath, "r");
    textureList[TEX_PLAYER] = IMG_LoadTexture_IO(renderer, texIn, true);
    SDL_SetTextureScaleMode(textureList[TEX_PLAYER], SDL_SCALEMODE_NEAREST);
    if (textureList[TEX_PLAYER] != NULL) {
        SDL_Log("LOADED PLAYER SPRITES");
    }

    // UI spritesheet
    strcpy_s(texPath, SDL_GetBasePath());
    strcat_s(texPath, "img\\UI.png");
    texIn = SDL_IOFromFile(texPath, "r");
    textureList[TEX_UI] = IMG_LoadTexture_IO(renderer, texIn, true);
    SDL_SetTextureScaleMode(textureList[TEX_UI], SDL_SCALEMODE_NEAREST);
    if (textureList[TEX_UI] != NULL) {
        SDL_Log("LOADED UI SPRITES");
    }

    // UI spritesheet
    strcpy_s(texPath, SDL_GetBasePath());
    strcat_s(texPath, "img\\items.png");
    texIn = SDL_IOFromFile(texPath, "r");
    textureList[TEX_ITEM] = IMG_LoadTexture_IO(renderer, texIn, true);
    SDL_SetTextureScaleMode(textureList[TEX_ITEM], SDL_SCALEMODE_NEAREST);
    if (textureList[TEX_ITEM] != NULL) {
        SDL_Log("LOADED ITEM SPRITES");
    }
};

extern SDL_FRect* font[256];
void loadFont();

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;