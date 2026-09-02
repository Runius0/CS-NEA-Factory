#include "main.h"

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static Player* player = new Player();
float x, y = 0;
int tick = 0;
float f_tick = 0;
const int TPS = 20;

static SDL_Surface* screenTint;
static SDL_Renderer* tintRenderer;

ItemStack* cursorItem;


// temporary building selection variable
MACHINE_ID selectedMachine = MACHINE_CONVEYOR;
UIElement hotbar(0, 0, 8, 1);
int hotbarSlot = 0;
UIElement mainInventory(0, 64, 8, 4);
bool inventoryOpen = false;

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

    screenTint = SDL_CreateSurface(1, 1, SDL_PIXELFORMAT_ABGR4444);
    tintRenderer = SDL_CreateSoftwareRenderer(screenTint);


    loadTextures(renderer);
    loadItems();
    hotbar.items[0][0] = new ItemStack(ITEM[1], 3);
    hotbar.items[1][0] = new ItemStack(ITEM[2], 32);
    hotbar.items[2][0] = new ItemStack(ITEM[3], 32);
    hotbar.items[3][0] = new ItemStack(ITEM[4], 32);
    hotbar.items[4][0] = new ItemStack(ITEM[5], 32);

    cursorItem = new ItemStack(ITEM[2], 5);

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
           hotbarSlot = 0;
        }
        else if (event->key.scancode == SDL_SCANCODE_2) {
           hotbarSlot = 1;
        }
        else if (event->key.scancode == SDL_SCANCODE_3) {
           hotbarSlot = 2;
        }
        else if (event->key.scancode == SDL_SCANCODE_4) {
            hotbarSlot = 3;
        }
        else if (event->key.scancode == SDL_SCANCODE_5) {
            hotbarSlot = 4;
        }
        else if (event->key.scancode == SDL_SCANCODE_6) {
            hotbarSlot = 5;
        }
        else if (event->key.scancode == SDL_SCANCODE_7) {
            hotbarSlot = 6;
        }
        else if (event->key.scancode == SDL_SCANCODE_8) {
            hotbarSlot = 7;
        }
        else if (event->key.scancode == SDL_SCANCODE_E) {
            inventoryOpen = !inventoryOpen;
        }
    }
    else if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {

    }
    else if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    return SDL_APP_CONTINUE;
}


void ProcessPlayerInput(float mouseX, float mouseY, SDL_MouseButtonFlags mouseFlags, const bool* keyboardState) {
    player->movement(keyboardState);

    if (hotbarSlot != -1 && hotbar.items[hotbarSlot][0] != NULL) {
        // if mouse down, attempt to place building
        if (mouseFlags & SDL_BUTTON_MASK(1)) {
            // get world pos
            float cX = mouseX + player->getX() - SCREEN_WIDTH / 2;
            float cY = mouseY + player->getY() - SCREEN_HEIGHT / 2;
            // snap to grid
            surface.snapToGrid(&cX, &cY);
            // world x/y
            int worldX = (int)(cX / TILE_SIZE);
            int worldY = (int)(cY / TILE_SIZE);
            // place machine temporary code
            if (Machine::canPlace(&surface, worldX, worldY, 1, 1)) {
                Machine* newTile = ((MachineItem*)(hotbar.items[hotbarSlot][0]->type))->getNew(worldX, worldY, player->placingDirection);
                newTile->place(&surface);
            }

        }

    }

    if (mouseFlags & SDL_BUTTON_MASK(3)) {
        hotbarSlot = -1;

        // get world pos
        float cX = mouseX + player->getX() - SCREEN_WIDTH / 2;
        float cY = mouseY + player->getY() - SCREEN_HEIGHT / 2;
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

}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void* appstate)
{

    int w = 0, h = 0;
    const float scale = 1.0f;

    float x, y;
    SDL_MouseButtonFlags mouseFlags = SDL_GetMouseState(&x, &y);

    const bool* keyboardState = SDL_GetKeyboardState(NULL);
    if (!inventoryOpen) {
        ProcessPlayerInput(x, y, mouseFlags, keyboardState);
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

    // draw player
    player->draw(renderer);

    if (inventoryOpen) {
        SDL_FillSurfaceRect(screenTint, NULL, SDL_MapRGBA(SDL_GetPixelFormatDetails(SDL_PIXELFORMAT_ABGR4444), NULL, 0, 0, 0, 128));
        //SDL_SetSurfaceAlphaMod(screenTint, 32);
        SDL_Texture* tint = SDL_CreateTextureFromSurface(renderer, screenTint);
        SDL_RenderTexture(renderer, tint, NULL, NULL);
        SDL_DestroyTexture(tint);
        mainInventory.draw(renderer, x, y);

        hotbar.draw(renderer, x, y);

        if (cursorItem->getAmount() != 0) {
            cursorItem->draw(renderer, x, y, 2);
        }
    }
    else {
        // draw cursor
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        // get world pos
        x += player->getX() - SCREEN_WIDTH / 2;
        y += player->getY() - SCREEN_HEIGHT / 2;
        // snap to grid
        surface.snapToGrid(&x, &y);
        // remap to screen pos
        x -= player->getX() - SCREEN_WIDTH / 2;
        y -= player->getY() - SCREEN_HEIGHT / 2;

        if (hotbarSlot != -1 && hotbar.items[hotbarSlot][0] != NULL) {
            ((MachineItem*)(hotbar.items[hotbarSlot][0]->type))->drawPreview(renderer, x, y, player->placingDirection);
        }

        SDL_FRect cursorRect = { x, y, TILE_SIZE, TILE_SIZE };
        SDL_RenderRect(renderer, &cursorRect);

        hotbar.draw(renderer);

    }


    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
}

