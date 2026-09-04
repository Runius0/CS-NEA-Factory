#include "main.h"

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static Player* player = new Player();
float x, y = 0;
int tick = 0;
float pf_tick = 0;
float f_tick = 0;
float deltaTick = 0;
const int TPS = 20;

float playerCraftProgress = 0;
int playerSelectedCraft = -1;

bool machineMenuOpen = false;
Machine* openedMachine;

static SDL_Surface* screenTint;
static SDL_Renderer* tintRenderer;

ItemStack* cursorItem;


// temporary building selection variable
MACHINE_ID selectedMachine = MACHINE_CONVEYOR;
UIElement hotbar(0, 0, 8, 1);
int hotbarSlot = 0;
UIElement mainInventory(0, 64, 8, 4);
bool inventoryOpen = false;
bool craftsOpen = false;

World surface;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{

    surface.addChunk(0, 0);
    surface.addChunk(-1, -1);
    surface.addChunk(-1, 0);
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
    loadFont();
    loadRecipes();
    hotbar.items[0][0] = new ItemStack(ITEM[1], 50);
    hotbar.items[1][0] = new ItemStack(ITEM[2], 50);
    hotbar.items[2][0] = new ItemStack(ITEM[3], 50);
    hotbar.items[3][0] = new ItemStack(ITEM[4], 50);
    hotbar.items[4][0] = new ItemStack(ITEM[5], 50);

    mainInventory.insertItem(ITEM[1], 50);
    mainInventory.insertItem(ITEM[1], 50);
    mainInventory.insertItem(ITEM[2], 50);
    mainInventory.insertItem(ITEM[3], 50);
    mainInventory.insertItem(ITEM[4], 50);
    mainInventory.insertItem(ITEM[5], 50);

    cursorItem = NULL;

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
            craftsOpen = inventoryOpen;
            machineMenuOpen = false;
        }
    }
    else if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if (event->button.button == SDL_BUTTON_LEFT) {
            if (inventoryOpen) {
                int slotX, slotY;
                ItemStack* temp = hotbar.getSlot(event->button.x, event->button.y, &slotX, &slotY);
                if (temp != NULL) {
                    if (cursorItem != NULL && *temp == *cursorItem) {
                        cursorItem->take(temp->add(cursorItem->getAmount()));
                        if (cursorItem->getAmount() == 0) { cursorItem = NULL; }
                        hotbar.setItem(temp, slotX, slotY);
                    }
                    else {
                        hotbar.setItem(cursorItem, slotX, slotY);
                        cursorItem = temp;
                    }
                }
                else if (hotbar.getSlotValid(event->button.x, event->button.y, &slotX, &slotY)) {
                    hotbar.setItem(cursorItem, slotX, slotY);
                    cursorItem = NULL;
                }
                temp = mainInventory.getSlot(event->button.x, event->button.y, &slotX, &slotY);
                if (temp != NULL) {
                    if (cursorItem != NULL && *temp == *cursorItem) {
                        cursorItem->take(temp->add(cursorItem->getAmount()));
                        if (cursorItem->getAmount() == 0) { cursorItem = NULL; }
                        mainInventory.setItem(temp, slotX, slotY);
                    }
                    else {
                        mainInventory.setItem(cursorItem, slotX, slotY);
                        cursorItem = temp;
                    }
                }
                else if (mainInventory.getSlotValid(event->button.x, event->button.y, &slotX, &slotY)) {
                    mainInventory.setItem(cursorItem, slotX, slotY);
                    cursorItem = NULL;
                }

                if (machineMenuOpen) {
                    openedMachine->clickInventory(&hotbar, &mainInventory, &cursorItem, 320, 32, event->button.x, event->button.y);
                }
            }
            else {
                // get world pos
                float cX = event->button.x + player->getX() - SCREEN_WIDTH / 2;
                float cY = event->button.y + player->getY() - SCREEN_HEIGHT / 2;
                // snap to grid
                surface.snapToGrid(&cX, &cY);
                // world x/y
                int worldX = (int)(cX / TILE_SIZE);
                int worldY = (int)(cY / TILE_SIZE);
                if (surface.getTile(worldX, worldY)->solid) {
                    Machine* tile = (Machine*)surface.getTile(worldX, worldY);
                    if (tile->interract()) {
                        inventoryOpen = true;
                        openedMachine = tile;
                        machineMenuOpen = true;
                    }
                }
            }
        } if (event->button.button == SDL_BUTTON_RIGHT) {
            if (inventoryOpen) {
                int slotX, slotY;
                ItemStack* temp = hotbar.getSlot(event->button.x, event->button.y, &slotX, &slotY);
                if (temp != NULL) {
                    if (cursorItem != NULL && *temp == *cursorItem) {
                        cursorItem->take(temp->add(1));
                        if (cursorItem->getAmount() == 0) { cursorItem = NULL; }
                        hotbar.setItem(temp, slotX, slotY);
                    }
                    else if (cursorItem == NULL) {
                        cursorItem = new ItemStack(temp->type, temp->getAmount()/2);
                        temp->take(cursorItem->getAmount());
                        hotbar.setItem(temp, slotX, slotY);
                    }
                }
                else if (cursorItem != NULL && hotbar.getSlotValid(event->button.x, event->button.y, &slotX, &slotY)) {
                    hotbar.setItem(new ItemStack(cursorItem->type, 1), slotX, slotY);
                    cursorItem->take(1);
                    if (cursorItem->getAmount() == 0) { cursorItem = NULL; }
                }
                temp = mainInventory.getSlot(event->button.x, event->button.y, &slotX, &slotY);
                if (temp != NULL) {
                    if (cursorItem != NULL && *temp == *cursorItem) {
                        cursorItem->take(temp->add(1));
                        if (cursorItem->getAmount() == 0) { cursorItem = NULL; }
                        mainInventory.setItem(temp, slotX, slotY);
                    }
                    else if (cursorItem == NULL) {
                        cursorItem = new ItemStack(temp->type, temp->getAmount() / 2);
                        temp->take(cursorItem->getAmount());
                        mainInventory.setItem(temp, slotX, slotY);
                    }
                }
                else if (cursorItem != NULL && mainInventory.getSlotValid(event->button.x, event->button.y, &slotX, &slotY)) {
                    mainInventory.setItem(new ItemStack(cursorItem->type, 1), slotX, slotY);
                    cursorItem->take(1);
                    if (cursorItem->getAmount() == 0) { cursorItem = NULL; }
                }
            }
        }
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
            if (hotbar.items[hotbarSlot][0]->type->placeable && Machine::canPlace(&surface, worldX, worldY, 1, 1)) {
                Machine* newTile = ((MachineItem*)(hotbar.items[hotbarSlot][0]->type))->getNew(worldX, worldY, player->placingDirection);
                newTile->place(&surface);
                hotbar.items[hotbarSlot][0]->take(1);
                if (hotbar.items[hotbarSlot][0]->getAmount() == 0) {
                    hotbar.items[hotbarSlot][0] = 0;
                }
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
            int ID = ((Machine*)(toDestroy))->ID;
            Item* itemType = ITEM[((Machine*)(toDestroy))->ID];
            mainInventory.insertItem(itemType, 1 - hotbar.insertItem(itemType, 1));
            ((Machine*)(toDestroy))->clear(&surface);
        }

    }

}


bool checkPlayerCanCraft(Recipe* recipe) {
    ItemStack** Ingredients = recipe->getIngredients();
    int ingredientNum = 0;

    while (Ingredients[ingredientNum] != NULL) {
        ItemStack* ingredient = Ingredients[ingredientNum];
        if (mainInventory.countItem(ingredient->type) + hotbar.countItem(ingredient->type) < ingredient->getAmount()) {
            return false;
        }
        ingredientNum++;
    }
    return true;

}

void completeCraft(Recipe* recipe) {
    if (!checkPlayerCanCraft(recipe)) { return; }
    ItemStack** Ingredients = recipe->getIngredients();
    int ingredientNum = 0;

    while (Ingredients[ingredientNum] != NULL) {
        ItemStack* ingredient = Ingredients[ingredientNum];
        hotbar.takeItem(ingredient->type, ingredient->getAmount() - mainInventory.takeItem(ingredient->type, ingredient->getAmount()));
        ingredientNum++;
    }

    hotbar.insertItem(recipe->getResult()->type, recipe->getResult()->getAmount() - mainInventory.insertItem(recipe->getResult()->type, recipe->getResult()->getAmount()));
}

void ProcessMenuInput(float mouseX, float mouseY, SDL_MouseButtonFlags mouseFlags, const bool* keyboardState) {
}

void ProcessCraftsMenu(float mouseX, float mouseY, SDL_MouseButtonFlags mouseFlags, const bool* keyboardState) {
    drawUIBackground(renderer, 320, 32, 256, 384);
    SDL_SetRenderDrawColor(renderer, 36, 34, 52, 255);
    SDL_FRect recipesArea = { 328, 128, 240, 280 };
    SDL_RenderFillRect(renderer, &recipesArea);
    for (int i = 0; i < numRecipes[CRAFT]; i++) {
        int x = 332 + (i%6) * 40;
        int y = 132 + (i/6) * 40;
        drawUIBackground(renderer, x, y, 32, 32);
        recipeRegistry[CRAFT][i]->getResult()->draw(renderer, x, y, 2);
    }
    if (mouseX > 328 && mouseX < 568 && mouseY > 132) {
        int slotX = (mouseX - 328) / 40;
        int slotY = (mouseY - 128) / 40;
        int slotID = slotX + slotY * 6;
        if (slotID >= 0 && slotID < numRecipes[CRAFT]) {
            SDL_FRect cursorIcon = { SPRITE_SIZE * 3, 0, SPRITE_SIZE, SPRITE_SIZE };
            SDL_FRect drawPos = { 332 + slotX * 40, 132 + slotY * 40, 32, 32 };
            SDL_RenderTexture(renderer, textureList[TEX_UI], &cursorIcon, &drawPos);
            // TODO: fix the MASSIVE memory leak this stupid code causes (mostly just clear up the created arrays)
            Recipe* recipe = recipeRegistry[CRAFT][slotID];
            char* recipeText[20];
            int ingredientNumber = 1;

            char itemAmountString[5];
            int amount = recipe->getResult()->getAmount();
            int amountDigits = SDL_log10(amount) + 1;
            for (int i = 0; i < amountDigits; i++) {
                itemAmountString[amountDigits - i - 1] = (amount % 10) + 48;
                amount /= 10;
            }

            // insane C string concatenation fuckery wizard magic (100% consistent and blazingly fast)
            recipeText[0] = new char[40];
            memcpy(recipeText[0], itemAmountString, amountDigits);
            memcpy(recipeText[0]+amountDigits, "x ", 2);
            memcpy(recipeText[0]+amountDigits+2, recipe->getResult()->type->name, 32);

            recipeText[1] = new char[40];
            memcpy(recipeText[1], "", 1);

            recipeText[2] = new char[40];
            memcpy(recipeText[2], "INGREDIENTS", 12);

            ItemStack** Ingredients = recipe->getIngredients();
            int ingredientNum = 0;

            while (Ingredients[ingredientNum] != NULL) {
                recipeText[ingredientNum + 3] = new char[40];

                amount = Ingredients[ingredientNum]->getAmount();
                amountDigits = SDL_log10(amount) + 1;
                for (int i = 0; i < amountDigits; i++) {
                    itemAmountString[amountDigits - i - 1] = (amount % 10) + 48;
                    amount /= 10;
                }

                memcpy(recipeText[ingredientNum + 3], itemAmountString, amountDigits);
                memcpy(recipeText[ingredientNum + 3] + amountDigits, "x ", 2);
                memcpy(recipeText[ingredientNum + 3] + amountDigits + 2, Ingredients[ingredientNum]->type->name, 32);

                ingredientNum++;
            }

            recipeText[ingredientNum + 3] = new char[40];
            memcpy(recipeText[ingredientNum + 3], "", 1);



            recipeText[ingredientNum + 4] = new char[40];
            memcpy(recipeText[ingredientNum + 4], "TIME ", 5);

            amount = recipe->getTime() / TPS;
            amountDigits = SDL_log10(amount) + 1;
            if (amount == 0) {
                amountDigits = 1; // this will cause an error anywhere else in the code but this is the only place it's likely to occur, so only fix here for now.
            }
            for (int i = 0; i < amountDigits; i++) {
                itemAmountString[amountDigits - i - 1] = (amount % 10) + 48;
                amount /= 10;
            }

            memcpy(recipeText[ingredientNum + 4] + 5, itemAmountString, amountDigits);

            int decimalAmount = (recipe->getTime() % TPS) * 5;
            itemAmountString[0] = '.'; // add decimal point hardcoded as we know the length of the decimal
            for (int i = 0; i < 2; i++) {
                itemAmountString[2 - i] = (decimalAmount % 10) + 48;
                decimalAmount /= 10;
            }
            memcpy(recipeText[ingredientNum + 4] + amountDigits + 5, itemAmountString, 3);
            memcpy(recipeText[ingredientNum + 4] + amountDigits + 8, "", 1);


            drawTextStrings(renderer, mouseX, mouseY + 24, (char**)recipeText, ingredientNum + 5, 40 );

            float maxProgress = recipe->getTime();

            SDL_FillSurfaceRect(screenTint, NULL, SDL_MapRGBA(SDL_GetPixelFormatDetails(SDL_PIXELFORMAT_ABGR4444), NULL, 255, 255, 255, 128));
            SDL_FRect progressTint = { 332 + slotX * 40, 164 + slotY * 40 - 32.0f * (playerCraftProgress / maxProgress), 32, 32.0f * (playerCraftProgress/maxProgress)};
            SDL_Texture* tint = SDL_CreateTextureFromSurface(renderer, screenTint);
            SDL_RenderTexture(renderer, tint, NULL, &progressTint);
            SDL_DestroyTexture(tint);


            if (mouseFlags & SDL_BUTTON_MASK(1)) {
                if (playerSelectedCraft != slotID) {
                    playerSelectedCraft = slotID;
                    playerCraftProgress = 0;
                }
                if (!checkPlayerCanCraft(recipe)) {
                    playerCraftProgress = 0;
                    return;
                }
                playerCraftProgress+= deltaTick;
                if (playerCraftProgress >= maxProgress) {
                    playerCraftProgress = 0;
                    completeCraft(recipe);
                }
            }
            else {
                playerCraftProgress = 0;
            }
        }
        else {
            playerCraftProgress = 0;
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
    pf_tick = f_tick;
    f_tick = SDL_GetTicks() / (1000.0f / TPS);
    if (f_tick - tick >= 1) {
        tick++;
        surface.tick(tick);
    }

    deltaTick = f_tick - pf_tick;

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

        ProcessMenuInput(x, y, mouseFlags, keyboardState);

        mainInventory.draw(renderer, x, y);
        hotbar.draw(renderer, x, y);

        if (craftsOpen) {
            ProcessCraftsMenu(x, y, mouseFlags, keyboardState);
        }
        if (machineMenuOpen) {
            openedMachine->renderInventory(renderer, 320, 32, x, y);
        }

        if (cursorItem != NULL) {
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

