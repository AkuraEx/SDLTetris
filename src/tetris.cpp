#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include "entity.h"
#include "definitions.h"

using namespace std;

/* Global SDL objects */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *L_texture = NULL;
static SDL_Texture *Square_texture = NULL;
static SDL_Texture *Grid_texture = NULL;
static int S_width = 0;
static int S_height = 0;
static int L_width = 0;
static int L_height = 0;


double rotate = 90;
SDL_FRect grid_position;

Uint64 last_tick = 0;
Uint64 current_tick = 0;
Uint64 interval = 1000;
float delta_time;


// TODO:

// JUST MAKE 200 TETROMINOES INSTEAD
// YOU CAN KEEP THE GAMEOBJECT STRUCT, BUT SINCE THE IMPLEMENTATION LOGIC SHOULD BE 
// DIFFERENT, TREAT THE BLOCKS AND GAME OBJECTS AS SEPARATE THINGS. DO NOT TRY TO PUT ONE INSIDE THE OTHER
// FIX THAT WHEN YOU RETURN.
GameObject blocks[200];
int numBlocks = 1;
int curBlock = 0;


/* Runs once at startup */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_Surface *surface = NULL;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Tetris", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    surface = IMG_Load("./assets/L_block.png");
    if (!surface) {
        SDL_Log("Couldn't load image: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }



    // Load L Block
    L_width = surface->w;
    L_height = surface->h;

    L_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    if (!L_texture) {
        SDL_Log("Couldn't create texture: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Load Square Block
    surface = IMG_Load("./assets/Square_block.png");

    S_width = surface->w;
    S_height = surface->h;

    Square_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    if (!Square_texture) {
        SDL_Log("Couldn't create texture: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Load Grid
    surface = IMG_Load("./assets/tetris_grid.png");

    Grid_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    
    if (!Grid_texture) {
        SDL_Log("Couldn't create texture: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    grid_position.x = GRID_POS_X;
    grid_position.y = GRID_POS_Y;
    grid_position.w = GRID_POS_W;
    grid_position.h = GRID_POS_H;


    SpawnTetromino(L_Block, blocks, curBlock, L_texture, GRID_POS_X + 16, GRID_POS_Y + 16, 32, 32);
    numBlocks = curBlock;

    return SDL_APP_CONTINUE;
}


/* Handles SDL events */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    const bool *keyboard_state = SDL_GetKeyboardState(NULL);

    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }

    if (event->type == SDL_EVENT_KEY_DOWN) {
        SDL_KeyboardEvent key = event->key;
        if (key.repeat == 0) {
            if(keyboard_state[SDL_SCANCODE_UP] || keyboard_state[SDL_SCANCODE_Z]) {
                blocks[curBlock].rotateClockwise();
                if (blocks[curBlock].rotation >= 360) blocks[curBlock].rotation -= 360;  // Normalize
            } else if(keyboard_state[SDL_SCANCODE_X]) {
                blocks[curBlock].rotation -= 90;
                if (blocks[curBlock].rotation <= 0) blocks[curBlock].rotation += 360;
            }
        }
        if(keyboard_state[SDL_SCANCODE_LEFT]) {
                blocks[curBlock].position.x -= 32;
            } else if(keyboard_state[SDL_SCANCODE_RIGHT]) {
                blocks[curBlock].position.x += 32;
            } else if(keyboard_state[SDL_SCANCODE_DOWN]) {
                blocks[curBlock].position.y += 32;
            } else if(keyboard_state[SDL_SCANCODE_SPACE]) {
                blocks[curBlock].position.y = 896;
            }
        }

    return SDL_APP_CONTINUE;
}

void update() {
    current_tick = SDL_GetTicks();

    if( current_tick - last_tick >= interval) {
        blocks[curBlock].position.y += 32;
        last_tick = current_tick;
        if(interval > 250) {
            interval -= 50;
        }
    }

    if(blocks[curBlock].position.y >= WINDOW_HEIGHT - 96) {
        blocks[curBlock].position.y = WINDOW_HEIGHT - 96;

        curBlock ++;
        numBlocks ++;
        if(numBlocks % 2 == 0) {
            GameObject_Init(&blocks[curBlock], L_texture, GRID_POS_X + 16, GRID_POS_Y + 16, L_width, L_height, true );
        } else {
            GameObject_Init(&blocks[curBlock], Square_texture, GRID_POS_X + 16, GRID_POS_Y + 16, S_width, S_height, true );
        }
    }
}

/* Runs once per frame to render */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    update();



    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);


    // Render Grid
    SDL_RenderTexture(renderer, Grid_texture, NULL, &grid_position);

    // Render Blocks
    for (int i = 0; i < numBlocks; i++) {
        GameObject_Render(renderer, &blocks[i]);
    }


    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

/* Runs once at shutdown */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    SDL_DestroyTexture(L_texture);
    SDL_DestroyTexture(Square_texture);
    // SDL will handle window and renderer cleanup
}
