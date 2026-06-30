#pragma once

#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "src/core/world.h"
#include "src/core/player.h"
#include "src/core/uiElement.h"

// content
#include "content/data/machines.h"
#include "content/data/items.h"