#include "score.h"

int score = 0;
std::string scoreString = "";
SDL_FRect srcrect = {0, 0, 32, 32}; 
SDL_FRect dstrect = {NEXT_POS_X, 424, 32, 32};

void addScore(int cleared) {
    switch(cleared) {
                case(1):
                    score += SINGLE;
                    break;
                case(2):
                    score += DOUBLE;
                    break;
                case(3):
                    score += TRIPLE;
                    break;
                case(4):
                    score += TETRIS;
                    break;
            }
}

void renderScore(SDL_Renderer* renderer) {
    scoreString = std::to_string(score);
    for(int i = 0; i < scoreString.size(); i ++) {
        dstrect.x = NEXT_POS_X + (32 * i) + 32;
        srcrect.x = 32 * (scoreString[i] - '0');
        SDL_RenderTexture(renderer, Numbers_texture, &srcrect, &dstrect); 
    }
}