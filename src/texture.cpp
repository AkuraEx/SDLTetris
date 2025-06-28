#include "texture.h"
#include "definitions.h"

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
SDL_Texture *Background_texture = nullptr;
SDL_Texture *Numbers_texture = nullptr;
SDL_Texture *Score_texture = nullptr;
SDL_Texture *Level_texture = nullptr;
SDL_Texture *Lines_texture = nullptr;
SDL_Texture *Logo_texture = nullptr;
SDL_Texture *Credits_texture = nullptr;
SDL_Texture *Game_over_texture = nullptr;

SDL_FRect background_position;
SDL_FRect grid_position;
SDL_FRect next_position;
SDL_FRect hold_position;
SDL_FRect score_position;
SDL_FRect level_position;
SDL_FRect lines_position;
SDL_FRect logo_position;
SDL_FRect credits_position;

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
        surface = IMG_Load("./assets/tetris_grid_B.png");

        Grid_texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);
        
        if (!Grid_texture) {
            SDL_Log("Couldn't create texture: %s", SDL_GetError());
            return SDL_APP_FAILURE;
        }

        // Load Next
        surface = IMG_Load("./assets/next_B.png");

        Next_texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);
        
        if (!Next_texture) {
            SDL_Log("Couldn't create texture: %s", SDL_GetError());
            return SDL_APP_FAILURE;
        }

        // Load Hold
        surface = IMG_Load("./assets/hold_B.png");

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

        // Load Background
        surface = IMG_Load("./assets/bad_background.png");

        Background_texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);
        
        if (!Background_texture) {
            SDL_Log("Couldn't create texture: %s", SDL_GetError());
            return SDL_APP_FAILURE;
        }

        // Load Numbers
        surface = IMG_Load("./assets/numbers.png");

        Numbers_texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);
        
        if (!Numbers_texture) {
            SDL_Log("Couldn't create texture: %s", SDL_GetError());
            return SDL_APP_FAILURE;
        }

        // Load Score
        surface = IMG_Load("./assets/Score.png");

        Score_texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);
        
        if (!Score_texture) {
            SDL_Log("Couldn't create texture: %s", SDL_GetError());
            return SDL_APP_FAILURE;
        }

        // Load Levels
        surface = IMG_Load("./assets/Level.png");

        Level_texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);
        
        if (!Level_texture) {
            SDL_Log("Couldn't create texture: %s", SDL_GetError());
            return SDL_APP_FAILURE;
        }

        // Load Lines
        surface = IMG_Load("./assets/Lines.png");

        Lines_texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);
        
        if (!Lines_texture) {
            SDL_Log("Couldn't create texture: %s", SDL_GetError());
            return SDL_APP_FAILURE;
        }

        // Load Logo
        surface = IMG_Load("./assets/Logo.png");

        Logo_texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);
        
        if (!Logo_texture) {
            SDL_Log("Couldn't create texture: %s", SDL_GetError());
            return SDL_APP_FAILURE;
        }

        // Load Credits
        surface = IMG_Load("./assets/Credits.png");

        Credits_texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);
        
        if (!Credits_texture) {
            SDL_Log("Couldn't create texture: %s", SDL_GetError());
            return SDL_APP_FAILURE;
        }

        // Load Game Over
        surface = IMG_Load("./assets/Game_Over2.png");

        Game_over_texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);
        
        if (!Game_over_texture) {
            SDL_Log("Couldn't create texture: %s", SDL_GetError());
            return SDL_APP_FAILURE;
        }

        grid_position = {GRID_POS_X, GRID_POS_Y, GRID_POS_W, GRID_POS_H};
        next_position = {NEXT_POS_X, NEXT_POS_Y, NEXT_POS_W, NEXT_POS_H};
        hold_position = {HOLD_POS_X, HOLD_POS_Y, NEXT_POS_W, NEXT_POS_H};
        background_position = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
        score_position = {SCORE_POS_X, SCORE_POS_Y, SCORE_POS_W, SCORE_POS_H};
        level_position = {SCORE_POS_X, SCORE_POS_Y + 256, SCORE_POS_W, SCORE_POS_H};
        lines_position = {SCORE_POS_X, SCORE_POS_Y + 128, SCORE_POS_W, SCORE_POS_H};
        logo_position = {LOGO_POS_X, LOGO_POS_Y, LOGO_POS_W, LOGO_POS_H};
        credits_position = {CREDITS_POS_X, CREDITS_POS_Y, CREDITS_POS_W, CREDITS_POS_H};

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
    SDL_DestroyTexture(Background_texture);
    SDL_DestroyTexture(Score_texture);
    SDL_DestroyTexture(Level_texture);
    SDL_DestroyTexture(Lines_texture);
    SDL_DestroyTexture(Logo_texture);
    SDL_DestroyTexture(Credits_texture);
    SDL_DestroyTexture(Game_over_texture);
}