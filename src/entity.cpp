#include "entity.h"
#include <iostream>

extern Tetromino block;  // Access to global blocks array
extern Tile board[BOARDHEIGHT][BOARDWIDTH];


void drawTetromino(const Tetromino& tetromino, SDL_Renderer* renderer, SDL_Texture* blockTexture) {
    for (int i = 0; i < TETROMINOGRID; ++i) {
        for (int j = 0; j < TETROMINOGRID; ++j) {
            if (tetromino.shape[i][j] != 0) {
                SDL_FRect destRect = {
                    static_cast<float>(tetromino.x + j * BLOCKSIZE),
                    static_cast<float>(tetromino.y + i * BLOCKSIZE),
                    static_cast<float>(BLOCKSIZE),
                    static_cast<float>(BLOCKSIZE)
                };
                SDL_RenderTexture(renderer, blockTexture, nullptr, &destRect);
            }
        }
    }
}


void SpawnTetromino(Grid3x3 blockType, SDL_Texture* texture, int startX, int startY, int blockW, int blockH) {
    block = Tetromino(blockType, startX, startY, texture);
}

