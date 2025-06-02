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

// Make a Board State
// 2d Matrix
// Collision


Tetromino blocks[200];
GameObject objects[200];
int numBlocks = 1;
int curBlock = 0;

// Track Collision
// It's all just math from here on out...
int board[BOARDHEIGHT][BOARDWIDTH] = {0};


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

    surface = IMG_Load("./assets/L_Tetromino.png");
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
    surface = IMG_Load("./assets/Square_Tetromino.png");

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


    SpawnTetromino(L_Block, curBlock, L_texture, GRID_POS_X + 16, GRID_POS_Y + 16, 32, 32);

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
            } else if(keyboard_state[SDL_SCANCODE_X]) {
                blocks[curBlock].rotateCounterClockwise();
            }
        }
        if(keyboard_state[SDL_SCANCODE_LEFT]) {
                blocks[curBlock].x -= 32;
            } else if(keyboard_state[SDL_SCANCODE_RIGHT]) {
                blocks[curBlock].x += 32;
            } else if(keyboard_state[SDL_SCANCODE_DOWN]) {
                blocks[curBlock].y += 32;
            } else if(keyboard_state[SDL_SCANCODE_SPACE]) {
                blocks[curBlock].y = 608;
            }
        }

    return SDL_APP_CONTINUE;
}

void update() {
    current_tick = SDL_GetTicks();

    if( current_tick - last_tick >= interval) {
        blocks[curBlock].y += 32;
        last_tick = current_tick;
        if(interval > 250) {
            interval -= 50;
        }
    }

    if(blocks[curBlock].y >= WINDOW_HEIGHT - 176) {
        blocks[curBlock].y = WINDOW_HEIGHT - 176;
        blocks[curBlock].settleBlock();

        curBlock ++;
        numBlocks ++;
        if(numBlocks % 2 == 0) {
            SpawnTetromino(L_Block, curBlock, L_texture, GRID_POS_X + 16, GRID_POS_Y + 16, 32, 32);
        } else {
            SpawnTetromino(Square_Block, curBlock, Square_texture, GRID_POS_X + 16, GRID_POS_Y + 16, 32, 32);
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
        drawTetromino(blocks[i], renderer, blocks[i].texture);
    }


    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

/* Runs once at shutdown */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    SDL_DestroyTexture(L_texture);
    SDL_DestroyTexture(Square_texture);
    SDL_DestroyTexture(Grid_texture);
    // SDL will handle window and renderer cleanup
}
