#include "main.h"

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static Player* player = new Player();
float x, y = 0;


World surface;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{

    surface.addChunk(0, 0);
    surface.addChunk(-1, -1);
    surface.addChunk(0, -1);

    /* Create the window */
    if (!SDL_CreateWindowAndRenderer("Hello World", 800, 600, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    loadTextures(renderer);

    return SDL_APP_CONTINUE;
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    if (event->type == SDL_EVENT_KEY_DOWN) {

    }
    else if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        float x, y;
        SDL_GetMouseState(&x, &y);
        // get world pos
        x += player->getX() - SCREEN_WIDTH / 2;
        y += player->getY() - SCREEN_HEIGHT / 2;
        // snap to grid
        surface.snapToGrid(&x, &y);
        // world x/y
        int worldX = (int)(x / TILE_SIZE);
        int worldY = (int)(y / TILE_SIZE);
        // place machine temporary code
        Machine* newTile = new Conveyor(worldX, worldY);
        newTile->place(&surface);
    }
    else if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    return SDL_APP_CONTINUE;
}




/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void* appstate)
{

    int w = 0, h = 0;
    const float scale = 1.0f;

    const bool* keyboardState = SDL_GetKeyboardState(NULL);
    player->movement(keyboardState);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    /* Center the message and scale it up */
    SDL_GetRenderOutputSize(renderer, &w, &h);
    SDL_SetRenderScale(renderer, scale, scale);

    surface.draw(renderer, player->getX(), player->getY());

    // draw cursor
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    float x, y;
    SDL_GetMouseState(&x, &y);
    // get world pos
    x += player->getX() - SCREEN_WIDTH/2;
    y += player->getY() - SCREEN_HEIGHT / 2;
    // snap to grid
    surface.snapToGrid(&x, &y);
    // remap to screen pos
    x -= player->getX() - SCREEN_WIDTH / 2;
    y -= player->getY() - SCREEN_HEIGHT / 2;

    Conveyor::DrawPreview(renderer, x, y);

    SDL_FRect cursorRect = {x, y, TILE_SIZE, TILE_SIZE};
    SDL_RenderRect(renderer, &cursorRect);

    // draw player
    player->draw(renderer);

    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
}

