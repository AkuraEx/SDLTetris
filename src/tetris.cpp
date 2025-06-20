#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include "entity.h"
#include "definitions.h"
#include <random>
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
static SDL_Texture *RL_texture = NULL;
static SDL_Texture *L_textureA = NULL;
static SDL_Texture *T_textureA = NULL;
static SDL_Texture *Square_textureA = NULL;
static SDL_Texture *R_textureA = NULL;
static SDL_Texture *Long_textureA = NULL;
static SDL_Texture *Left_textureA = NULL;
static SDL_Texture *RL_textureA = NULL;
static SDL_Texture *Grid_texture = NULL;
static SDL_Texture *Next_texture = NULL;
static SDL_Texture *Hold_texture = NULL;



SDL_FRect grid_position;
SDL_FRect next_position;
SDL_FRect hold_position;

Uint64 last_tick = 0;
Uint64 current_tick = 0;
Uint64 interval = 1000;
float delta_time;



Tetromino hold;
Tetromino block;
Tetromino nextBlock;
Tetromino ghostBlock;
bool holdUsed = false;
int numBlocks = 1;
int curBlock = 0;

Tile board[BOARDHEIGHT][BOARDWIDTH] = {0, NULL};

void RandomTetromino(Tetromino& block) {
    static std::mt19937 rng(static_cast<unsigned int>(time(nullptr)));
    std::uniform_int_distribution<int> dist(0, 6);

    int randomIndex = dist(rng);
    switch (randomIndex) {
        case 0:
            block.shape = L_Block;
            block.texture = L_texture;
            break;
        case 1:
            block.shape = Square_Block;
            block.texture = Square_texture;
            break;
        case 2:
            block.shape = T_Block;
            block.texture = T_texture;
            break;
        case 3:
            block.shape = R_Block;
            block.texture = R_texture;
            break;
        case 4:
            block.shape = Left_Block;
            block.texture = Left_texture;
            break;
        case 5:
            block.shape = Long_Block;
            block.texture = Long_texture;
            break;
        case 6:
            block.shape = RL_Block;
            block.texture = RL_texture;
            break;
    }
}


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
    L_textureA = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_SetTextureAlphaMod(L_textureA, 100);
    SDL_DestroySurface(surface);

    if (!L_texture) {
        SDL_Log("Couldn't create texture: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }


    // Load Square Block
    surface = IMG_Load("./assets/Square_tetromino.png");
    
    Square_texture = SDL_CreateTextureFromSurface(renderer, surface);
    Square_textureA = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_SetTextureAlphaMod(Square_textureA, 100);
    SDL_DestroySurface(surface);

    if (!Square_texture) {
        SDL_Log("Couldn't create texture: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Load T Block
    surface = IMG_Load("./assets/T_tetromino.png");
    
    T_texture = SDL_CreateTextureFromSurface(renderer, surface);
    T_textureA = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_SetTextureAlphaMod(T_textureA, 100);
    SDL_DestroySurface(surface);

    if (!T_texture) {
        SDL_Log("Couldn't create texture: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    

    // Load T Block
    surface = IMG_Load("./assets/R_tetromino.png");
    
    R_texture = SDL_CreateTextureFromSurface(renderer, surface);
    R_textureA = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_SetTextureAlphaMod(R_textureA, 100);
    SDL_DestroySurface(surface);

    if (!R_texture) {
        SDL_Log("Couldn't create texture: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Load Left Block
    surface = IMG_Load("./assets/Left_tetromino.png");

    Left_texture = SDL_CreateTextureFromSurface(renderer, surface);
    Left_textureA = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_SetTextureAlphaMod(Left_textureA, 100);
    SDL_DestroySurface(surface);

    if (!Left_texture) {
        SDL_Log("Couldn't create texture: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Load Long Block
    surface = IMG_Load("./assets/Long_Tetromino.png");

    Long_texture = SDL_CreateTextureFromSurface(renderer, surface);
    Long_textureA = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_SetTextureAlphaMod(Long_textureA, 100);
    SDL_DestroySurface(surface);

    if (!Long_texture) {
        SDL_Log("Couldn't create texture: %s", SDL_GetError());
    }

    // Load RL Block
    surface = IMG_Load("./assets/RL_Tetromino.png");

    RL_texture = SDL_CreateTextureFromSurface(renderer, surface);
    RL_textureA = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_SetTextureAlphaMod(RL_textureA, 100);
    SDL_DestroySurface(surface);

    if (!RL_texture) {
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

    // Load Next
    surface = IMG_Load("./assets/next.png");

    Next_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    
    if (!Next_texture) {
        SDL_Log("Couldn't create texture: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Load Hold
    surface = IMG_Load("./assets/hold.png");

    Hold_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    
    if (!Hold_texture) {
        SDL_Log("Couldn't create texture: %s", SDL_GetError());
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


    RandomTetromino(block);
    RandomTetromino(nextBlock);
    nextBlock.x = NEXT_POS_X + 32;
    nextBlock.y = NEXT_POS_Y + 32;
    hold.x = HOLD_POS_X + 32;
    hold.y = HOLD_POS_Y + 32;
    SpawnTetromino(block.shape, block.texture, SPAWN_X, GRID_POS_Y + 16, 32, 32);
    ghostBlock = block;
    ghostBlock.texture = getTransparentTexture(block.texture);

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
                ghostBlock.shape = block.shape;
            } else if(keyboard_state[SDL_SCANCODE_X] ){
                block.rotateCounterClockwise();
                ghostBlock.shape = block.shape;
            }
        }
        if(keyboard_state[SDL_SCANCODE_LEFT] && !block.checkWall(-BLOCKSIZE)){
                block.x -= 32;
                ghostBlock.x -= 32;
                ghostBlock.hardDrop();
            } else if(keyboard_state[SDL_SCANCODE_RIGHT] && !block.checkWall(BLOCKSIZE) ){
                block.x += 32;
                ghostBlock.x +=32;
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
                    RandomTetromino(nextBlock);
                    SpawnTetromino(block.shape, block.texture, SPAWN_X, GRID_POS_Y + 16, 32, 32);
                    ghostBlock = block;
                    ghostBlock.texture = getTransparentTexture(block.texture);
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
                    holdUsed = true;
                }
            }
        }

    return SDL_APP_CONTINUE;
}

void update() {
    current_tick = SDL_GetTicks();

    if(current_tick - last_tick >= interval) {

        if(!block.checkUnder()) {
            block.lock();
            holdUsed = false;
            clearLine();
            curBlock ++;
            numBlocks ++;


            block = nextBlock;
            RandomTetromino(nextBlock);
            SpawnTetromino(block.shape, block.texture, SPAWN_X, GRID_POS_Y + 16, 32, 32);
            ghostBlock = block;
            ghostBlock.texture = getTransparentTexture(block.texture);
            ghostBlock.hardDrop();


        } else {
            block.y += 32;
        }
        last_tick = current_tick;
        if(interval > 250) {
            interval -= 7;
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
    SDL_RenderTexture(renderer, Next_texture, NULL, &next_position);
    SDL_RenderTexture(renderer, Hold_texture, NULL, &hold_position);

    // Render Blocks
    drawTetromino(nextBlock, renderer, nextBlock.texture);
    drawTetromino(block, renderer, block.texture);
    drawTetromino(hold, renderer, hold.texture);
    drawTetromino(ghostBlock, renderer, ghostBlock.texture);

    // Render Board
    renderBoard(renderer);

    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

/* Runs once at shutdown */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    SDL_DestroyTexture(L_texture);
    SDL_DestroyTexture(Square_texture);
    SDL_DestroyTexture(Long_texture);
    SDL_DestroyTexture(R_texture);
    SDL_DestroyTexture(RL_texture);
    SDL_DestroyTexture(T_texture);
    SDL_DestroyTexture(Left_texture);
    SDL_DestroyTexture(Grid_texture);
    SDL_DestroyTexture(Next_texture);
    SDL_DestroyTexture(Hold_texture);
    // SDL will handle window and renderer cleanup
}
