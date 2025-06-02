#include "entity.h"
#include <iostream>

extern Tetromino blocks[200];  // Access to global blocks array

void GameObject_Init(GameObject* obj, SDL_Texture* texture, float x, float y, float w, float h, bool visible) {
    obj->texture = texture;
    obj->position = {x, y, w, h};
    obj->origin = {w / 2.0f, h / 2.0f};
    obj->visible = visible;
}

void drawTetromino(const Tetromino& tetromino, SDL_Renderer* renderer, SDL_Texture* blockTexture) {
    for (int i = 0; i < Tetromino_size; ++i) {
        for (int j = 0; j < Tetromino_size; ++j) {
            if (tetromino.shape[i][j] != 0) {
                SDL_FRect destRect = {
                    static_cast<float>(tetromino.x + j * Block_size),
                    static_cast<float>(tetromino.y + i * Block_size),
                    static_cast<float>(Block_size),
                    static_cast<float>(Block_size)
                };
                SDL_RenderTexture(renderer, blockTexture, nullptr, &destRect);
            }
        }
    }
}

void GameObject_Render(SDL_Renderer* renderer, const GameObject* obj) {
    if (obj->visible) {
        SDL_RenderTexture(renderer, obj->texture, nullptr, &obj->position);
    }
}

void SpawnTetromino(Grid4x4 blockType, int& destIndex, SDL_Texture* texture, int startX, int startY, int blockW, int blockH) {
    blocks[destIndex] = Tetromino(blockType, startX, startY, texture);
}
