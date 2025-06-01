#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <array>

constexpr int Tetromino_size = 4;
constexpr int Block_size = 32;

using Grid4x4 = std::array<std::array<int, Tetromino_size>, Tetromino_size>;

struct Tetromino {
    Grid4x4 shape;
    int x, y;

    Tetromino(const Grid4x4& initialShape, int startX, int startY)
        : shape(initialShape), x(startX), y(startY) {}

    void rotateClockwise() {
        Grid4x4 rotated{};
        for (int i = 0; i < Tetromino_size; ++i) {
            for (int j = 0; j < Tetromino_size; ++j) {
                rotated[j][Tetromino_size - 1 - i] = shape[i][j];
            shape = rotated;
            }
        }
    }

    void rotateCounterClockwise() {
        Grid4x4 rotated{};
        for (int i = 0; i < Tetromino_size; ++i) {
            for (int j = 0; j < Tetromino_size; ++j) {
                rotated[Tetromino_size - 1 - j][i] = shape[i][j];
            shape = rotated;
            }
        }
    }      


};


typedef struct {
    SDL_Texture* texture;
    SDL_FRect position;
    SDL_FPoint origin;
    bool visible;
} GameObject;

const Grid4x4 L_Block = {{
    {1, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0}
}};

const Grid4x4 Square_Block = {{
    {1, 1, 0, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
}};

void GameObject_Init(GameObject* obj, SDL_Texture* texture, float x, float y, float w, float h, bool visible);

void GameObject_Render(SDL_Renderer* renderer, const GameObject* obj);

void drawTetromino(const Tetromino& tetromino, SDL_Renderer* renderer, SDL_Texture* blockTexture);

void SpawnTetromino(Grid4x4 blockType, GameObject* destArray, int& destIndex, SDL_Texture* texture, int startX, int startY, int blockW, int blockH);