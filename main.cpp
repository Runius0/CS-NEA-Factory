#include "main.h"

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static Player* player = new Player();
float x, y = 0;
int tick = 0;
float f_tick = 0;
const int TPS = 20;

// temporary building selection variable
MACHINE_ID selectedMachine = MACHINE_CONVEYOR;


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
        if (event->key.scancode == SDL_SCANCODE_R) {
            player->placingDirection = (Direction)((player->placingDirection + 1) % 4);
        }
        else if (event->key.scancode == SDL_SCANCODE_1) {
            selectedMachine = MACHINE_CONVEYOR;
        }
        else if (event->key.scancode == SDL_SCANCODE_2) {
            selectedMachine = MACHINE_IMPORTER;
        }
        else if (event->key.scancode == SDL_SCANCODE_3) {
            selectedMachine = MACHINE_EXPORTER;
        }
    }
    else if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {

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

    // if mouse down, attempt to place building
    float x, y;
    if (SDL_GetMouseState(&x, &y) & SDL_BUTTON_MASK(1)) {
        // get world pos
        x += player->getX() - SCREEN_WIDTH / 2;
        y += player->getY() - SCREEN_HEIGHT / 2;
        // snap to grid
        surface.snapToGrid(&x, &y);
        // world x/y
        int worldX = (int)(x / TILE_SIZE);
        int worldY = (int)(y / TILE_SIZE);
        // place machine temporary code
        if (Machine::canPlace(&surface, worldX, worldY, 1, 1)) {
            Machine* newTile = NewMachine(selectedMachine, worldX, worldY, player->placingDirection);
            newTile->place(&surface);
        }

    }
    if (SDL_GetMouseState(&x, &y) & SDL_BUTTON_MASK(3)) {
        // get world pos
        float cX = x + player->getX() - SCREEN_WIDTH / 2;
        float cY = y + player->getY() - SCREEN_HEIGHT / 2;
        // snap to grid
        surface.snapToGrid(&cX, &cY);
        // world x/y
        int worldX = (int)(cX / TILE_SIZE);
        int worldY = (int)(cY / TILE_SIZE);
        // destroy machine temporary code
        Tile* toDestroy = surface.getTile(worldX, worldY);
        if (toDestroy->solid) {
            ((Machine*)(toDestroy))->clear(&surface);
        }

    }



    // increment tick
    f_tick = SDL_GetTicks() / (1000.0f / TPS);
    if (f_tick - tick >= 1) {
        tick++;
        surface.tick(tick);
    }


    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    /* Center the message and scale it up */
    SDL_GetRenderOutputSize(renderer, &w, &h);
    SDL_SetRenderScale(renderer, scale, scale);

    surface.draw(renderer, player->getX(), player->getY());

    // draw cursor
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    // get world pos
    x += player->getX() - SCREEN_WIDTH/2;
    y += player->getY() - SCREEN_HEIGHT / 2;
    // snap to grid
    surface.snapToGrid(&x, &y);
    // remap to screen pos
    x -= player->getX() - SCREEN_WIDTH / 2;
    y -= player->getY() - SCREEN_HEIGHT / 2;

    DrawMachinePreview(selectedMachine, renderer, x, y, player->placingDirection);

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

