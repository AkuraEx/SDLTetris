#include "entity.h"

void GameObject_Init(GameObject* obj, SDL_Texture* texture, float x, float y, float w, float h, bool visible) {
    obj -> texture = texture;
    obj -> position.x = x;
    obj -> position.y = y;
    obj -> position.w = w;
    obj -> position.h = h;
    obj -> origin.x = w / 2.0f;
    obj -> origin.y = h / 2.0f;
    obj -> visible = true;
}



void drawTetromino(const Tetromino& tetromino, SDL_Renderer* renderer, SDL_Texture* blockTexture) {
    for (int i = 0; i < Tetromino_size; ++i) {
        for ( int j = 0; j < Tetromino_size; ++j) {
            if (tetromino.shape[i][j] != 0) {
                SDL_FRect destRect = {
                    (tetromino.x + j) * Block_size,
                    (tetromino.y + i) * Block_size,
                    Block_size,
                    Block_size
                };
                SDL_RenderTexture(renderer, blockTexture, nullptr, &destRect);
            }
        }   
    }
}


void SpawnTetromino(Grid4x4 blockType, GameObject* destArray, int& destIndex, SDL_Texture* texture, int startX, int startY, int blockW, int blockH) {
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            if (blockType[row][col] == 1) {
                float x = startX + col * blockW;
                float y = startY + row * blockH;
                GameObject_Init(&destArray[destIndex], texture, x, y, blockW, blockH, true);
                destIndex++;
            }
        }
    }
}