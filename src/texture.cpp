#include "texture.h"

SDL_Texture *L_texture = nullptr, *L_textureA = nullptr;
SDL_Texture *T_texture = nullptr, *T_textureA = nullptr;
SDL_Texture *Square_texture = nullptr, *Square_textureA = nullptr;
SDL_Texture *R_texture = nullptr, *R_textureA = nullptr;
SDL_Texture *Long_texture = nullptr, *Long_textureA = nullptr;
SDL_Texture *Left_texture = nullptr, *Left_textureA = nullptr;
SDL_Texture *RL_texture = nullptr, *RL_textureA = nullptr;
SDL_Texture *Grid_texture = nullptr;
SDL_Texture *Next_texture = nullptr;
SDL_Texture *Hold_texture = nullptr;
SDL_Texture *White_texture = nullptr;

bool loadTextures(SDL_Renderer* renderer) {
        SDL_Surface *surface = NULL;

        // Load L Block
        surface = IMG_Load("./assets/L_Tetromino.png");
        if (!surface) {
            SDL_Log("Couldn't load image: %s", SDL_GetError());
            return SDL_APP_FAILURE;
        }

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

        // Load White
        surface = IMG_Load("./assets/white.png");

        White_texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);
        
        if (!White_texture) {
            SDL_Log("Couldn't create texture: %s", SDL_GetError());
            return SDL_APP_FAILURE;
        }

        return true;
    }

void destroyTextures() {
    SDL_DestroyTexture(L_texture);
    SDL_DestroyTexture(L_textureA);
    SDL_DestroyTexture(Square_texture);
    SDL_DestroyTexture(Square_textureA);
    SDL_DestroyTexture(Long_texture);
    SDL_DestroyTexture(Long_textureA);
    SDL_DestroyTexture(R_texture);
    SDL_DestroyTexture(R_textureA);
    SDL_DestroyTexture(RL_texture);
    SDL_DestroyTexture(RL_textureA);
    SDL_DestroyTexture(T_texture);
    SDL_DestroyTexture(T_textureA);
    SDL_DestroyTexture(Left_texture);
    SDL_DestroyTexture(Left_textureA);
    SDL_DestroyTexture(Grid_texture);
    SDL_DestroyTexture(Next_texture);
    SDL_DestroyTexture(Hold_texture);
}