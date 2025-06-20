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


Uint64 last_tick = 0;
Uint64 current_tick = 0;
Uint64 interval = 1000;
Uint64 intervalB = 1000;
Uint64 tempInterval = 200;
float delta_time;

Tetromino hold;
Tetromino block;
Tetromino nextBlock;
Tetromino ghostBlock;

SDL_FRect background_position;
SDL_FRect grid_position;
SDL_FRect next_position;
SDL_FRect hold_position;

bool holdUsed = false;
bool clear = false;
int numBlocks = 1;
int curBlock = 0;
int cleared = 0;
int Line = 0;

Tile board[BOARDHEIGHT][BOARDWIDTH] = {0, NULL};


SDL_Texture* getTransparentTexture(SDL_Texture* tex) {
    if (tex == L_texture) return L_textureA;
    if (tex == T_texture) return T_textureA;
    if (tex == Square_texture) return Square_textureA;
    if (tex == R_texture) return R_textureA;
    if (tex == Long_texture) return Long_textureA;
    if (tex == Left_texture) return Left_textureA;
    if (tex == RL_texture) return RL_textureA;
    return tex; // fallback (non-transparent)
}

void renderFullFrame() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_RenderTexture(renderer, Background_texture, NULL, &background_position);
    SDL_RenderTexture(renderer, Grid_texture, NULL, &grid_position);
    SDL_RenderTexture(renderer, Next_texture, NULL, &next_position);
    SDL_RenderTexture(renderer, Hold_texture, NULL, &hold_position);

    drawTetromino(nextBlock, renderer, nextBlock.texture);
    drawTetromino(block, renderer, block.texture);
    drawTetromino(hold, renderer, hold.texture);
    drawTetromino(ghostBlock, renderer, ghostBlock.texture);

    renderBoard(renderer);
    SDL_RenderPresent(renderer);
}

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

    if (!loadTextures(renderer)) {
        SDL_Log("Failed to load textures");
        return SDL_APP_FAILURE;
    }

    

    grid_position.x = GRID_POS_X;
    grid_position.y = GRID_POS_Y;
    grid_position.w = GRID_POS_W;
    grid_position.h = GRID_POS_H;


    next_position.x = NEXT_POS_X;
    next_position.y = NEXT_POS_Y;
    next_position.h = NEXT_POS_H;
    next_position.w = NEXT_POS_W;


    hold_position.x = HOLD_POS_X;
    hold_position.y = HOLD_POS_Y;
    hold_position.h = NEXT_POS_H;
    hold_position.w = NEXT_POS_W;

    
    background_position.x = 0;
    background_position.y = 0;
    background_position.h = WINDOW_HEIGHT;
    background_position.w = WINDOW_WIDTH;
    


    randomTetromino(block);
    randomTetromino(nextBlock);
    nextBlock.x = NEXT_POS_X + 32;
    nextBlock.y = NEXT_POS_Y + 32;
    hold.x = HOLD_POS_X + 32;
    hold.y = HOLD_POS_Y + 32;
    SpawnTetromino(block.shape, block.texture, SPAWN_X, GRID_POS_Y + 16, 32, 32);
    ghostBlock = block;
    ghostBlock.texture = getTransparentTexture(block.texture);
    ghostBlock.hardDrop();

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
                ghostBlock = block;
                ghostBlock.texture = getTransparentTexture(block.texture);
                ghostBlock.hardDrop();
            } else if(keyboard_state[SDL_SCANCODE_X] ){
                block.rotateCounterClockwise();
                ghostBlock = block;
                ghostBlock.texture = getTransparentTexture(block.texture);
                ghostBlock.hardDrop();
            }
        }
        if(keyboard_state[SDL_SCANCODE_LEFT] && !block.checkWall(-BLOCKSIZE)){
                block.x -= 32;
                ghostBlock = block;
                ghostBlock.texture = getTransparentTexture(block.texture);
                ghostBlock.hardDrop();
            } else if(keyboard_state[SDL_SCANCODE_RIGHT] && !block.checkWall(BLOCKSIZE) ){
                block.x += 32;
                ghostBlock = block;
                ghostBlock.texture = getTransparentTexture(block.texture);
                ghostBlock.hardDrop();
            } else if(keyboard_state[SDL_SCANCODE_DOWN] && block.checkUnder()){
                block.y += 32;
            } else if(keyboard_state[SDL_SCANCODE_SPACE]){
                block.hardDrop();
                last_tick = 0;
            } else if(keyboard_state[SDL_SCANCODE_C] && holdUsed == false) {
                if(hold.texture == NULL) {
                    hold.texture = block.texture;
                    hold.shape = block.shape;
                    block = nextBlock;
                    randomTetromino(nextBlock);
                    SpawnTetromino(block.shape, block.texture, SPAWN_X, GRID_POS_Y + 16, 32, 32);
                    ghostBlock = block;
                    ghostBlock.texture = getTransparentTexture(block.texture);
                    ghostBlock.hardDrop();
                    holdUsed = true;
                } else {
                    Tetromino temp = block;
                    block = hold;
                    block.x = SPAWN_X;
                    block.y = GRID_POS_Y + 16;
                    hold.texture = temp.texture;
                    hold.shape = temp.shape;
                    ghostBlock = block;
                    ghostBlock.texture = getTransparentTexture(block.texture);
                    ghostBlock.hardDrop();
                    holdUsed = true;
                }
            }
        }

    return SDL_APP_CONTINUE;
}

void update() {
    current_tick = SDL_GetTicks();

    if(current_tick - last_tick >= interval) {
        interval = intervalB;

        if(clear) {
            removeLine(cleared, Line);
            clear = false;
        } else if(!block.checkUnder()) {
            block.lock();
            holdUsed = false;

            clearLine(White_texture, clear, cleared, Line);
            curBlock ++;
            numBlocks ++;


            block = nextBlock;
            randomTetromino(nextBlock);
            SpawnTetromino(block.shape, block.texture, SPAWN_X, GRID_POS_Y + 16, 32, 32);
            ghostBlock = block;
            ghostBlock.texture = getTransparentTexture(block.texture);
            ghostBlock.hardDrop();

            interval = tempInterval;

        } else {
            block.y += 32;
        }

        last_tick = current_tick;
        if(interval > 200) {
            interval -= 4;
            intervalB -= 4;
        }

    }
}

/* Runs once per frame to render */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    update();
    renderFullFrame();

    return SDL_APP_CONTINUE;
}

/* Runs once at shutdown */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    destroyTextures();
    // SDL will handle window and renderer cleanup
}
