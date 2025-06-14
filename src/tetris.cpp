#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include "entity.h"
#include "definitions.h"
#include <cstdlib>

using namespace std;

/* Global SDL objects */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *L_texture = NULL;
static SDL_Texture *T_texture = NULL;
static SDL_Texture *Square_texture = NULL;
static SDL_Texture *R_texture = NULL;
static SDL_Texture *Long_texture = NULL;
static SDL_Texture *Left_texture = NULL;
static SDL_Texture *Grid_texture = NULL;


SDL_FRect grid_position;

Uint64 last_tick = 0;
Uint64 current_tick = 0;
Uint64 interval = 1000;
float delta_time;


// TODO:

// Make a Board State
// 2d Matrix
// Collision


Tetromino block;
int numBlocks = 1;
int curBlock = 0;

// Track Collision
// It's all just math from here on out...
Tile board[BOARDHEIGHT][BOARDWIDTH] = {0, NULL};


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
    L_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    if (!L_texture) {
        SDL_Log("Couldn't create texture: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Load Square Block
    surface = IMG_Load("./assets/Square_Tetromino.png");

    Square_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    if (!Square_texture) {
        SDL_Log("Couldn't create texture: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Load T Block
    surface = IMG_Load("./assets/T_tetromino.png");
    
    T_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    if (!T_texture) {
        SDL_Log("Couldn't create texture: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    

    // Load T Block
    surface = IMG_Load("./assets/R_tetromino.png");
    
    R_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    if (!R_texture) {
        SDL_Log("Couldn't create texture: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Load Left Block
    surface = IMG_Load("./assets/Left_tetromino.png");

    Left_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    if (!Left_texture) {
        SDL_Log("Couldn't create texture: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Load Long Block
    surface = IMG_Load("./assets/Long_Tetromino.png");

    Long_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    if (!Long_texture) {
        SDL_Log("Couldn't create texture: %s", SDL_GetError());
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


    SpawnTetromino(L_Block, L_texture, GRID_POS_X - 16, GRID_POS_Y + 16, 32, 32);

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
            if(keyboard_state[SDL_SCANCODE_UP] || keyboard_state[SDL_SCANCODE_Z] ) {
                block.rotateClockwise();
            } else if(keyboard_state[SDL_SCANCODE_X] ){
                block.rotateCounterClockwise();
            }
        }
        if(keyboard_state[SDL_SCANCODE_LEFT] && !block.checkWall(-BLOCKSIZE)){
                block.x -= 32;
            } else if(keyboard_state[SDL_SCANCODE_RIGHT] && !block.checkWall(BLOCKSIZE) ){
                block.x += 32;
            } else if(keyboard_state[SDL_SCANCODE_DOWN]){
                block.y += 32;
            } else if(keyboard_state[SDL_SCANCODE_SPACE]){
                block.hardDrop();
            }
        }

    return SDL_APP_CONTINUE;
}

void update() {
    current_tick = SDL_GetTicks();

    if(current_tick - last_tick >= interval) {

        if(!block.checkUnder()) {
            block.lock();
            curBlock ++;
            numBlocks ++;

            if(current_tick % 6 == 0) {
                SpawnTetromino(L_Block, L_texture, GRID_POS_X + 16 , GRID_POS_Y + 16, 32, 32);
            } else if(current_tick % 6 == 1) {
                SpawnTetromino(Square_Block, Square_texture, GRID_POS_X + 16, GRID_POS_Y + 16, 32, 32);
            } else if(current_tick % 6 == 2) {
                SpawnTetromino(T_Block, T_texture, GRID_POS_X + 16, GRID_POS_Y + 16, 32, 32);
            } else if(current_tick % 6 == 3) {
                SpawnTetromino(R_Block, R_texture, GRID_POS_X + 16, GRID_POS_Y + 16, 32, 32);
            } else if(current_tick % 6 == 4) {
                SpawnTetromino(Left_Block, Left_texture, GRID_POS_X + 16, GRID_POS_Y + 16, 32, 32);
            } else {
                SpawnTetromino(Long_Block, Long_texture, GRID_POS_X + 16, GRID_POS_Y + 16, 32, 32);
            }


        } else {
            block.y += 32;
        }
        last_tick = current_tick;
        if(interval > 250) {
            interval -= 5;
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
        drawTetromino(block, renderer, block.texture);

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            if(board[i][j].fill == 1) {
                SDL_FRect temp;
                temp.x = j * 32 + OFFSET_X;
                temp.y = i * 32 + OFFSET_Y + 32;
                temp.h = 32;
                temp.w = 32;
                SDL_RenderTexture(renderer, board[i][j].texture, NULL, &temp);
            }
        }
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
