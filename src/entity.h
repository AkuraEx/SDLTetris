#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <array>
#include "definitions.h"

using Grid3x3 = std::array<std::array<int, TETROMINOGRID>, TETROMINOGRID>;
extern int board[BOARDHEIGHT][BOARDWIDTH];

struct Tetromino {
    Grid3x3 shape;
    int x, y; // Position in pixels
    SDL_Texture *texture;

    Tetromino() : x(0), y(0) {
        shape = {};
        texture = NULL;
    }

    Tetromino(const Grid3x3& initialShape, int startX, int startY, SDL_Texture *texture)
        : shape(initialShape), x(startX), y(startY), texture(texture) {}

    void rotateClockwise() {
        Grid3x3 rotated{};
        for (int i = 0; i < TETROMINOGRID; ++i) {
            for (int j = 0; j < TETROMINOGRID; ++j) {
                rotated[j][TETROMINOGRID - 1 - i] = shape[i][j];

            }
        }
        if(!checkCollision(rotated)) {
            shape = rotated;
        }
    }

    void rotateCounterClockwise() {
        Grid3x3 rotated{};
        for (int i = 0; i < TETROMINOGRID; ++i) {
            for (int j = 0; j < TETROMINOGRID; ++j) {
                rotated[TETROMINOGRID - 1 - j][i] = shape[i][j];
            }
        }

        if(!checkCollision(rotated)) {
            shape = rotated;
        }
    }

    
    /*
    void settleBlock() {
        for (int i = TETROMINOGRID - 1; i >= 0; --i) {
            for (int j = 0; j < TETROMINOGRID; ++j) {
                if(shape[i][j] == 1 && shape[3][j] == 0 && board[x / 32 - 10][(y + 32) / 32 - 1] != 1) {
                    shape[3][j] = 1;
                    shape[i][j] = 0;
                    board[x / 32 - 10][y / 32 - 1] = 1;
                } else if(shape[i][j] == 1 && shape[2][j] == 0 && board[x / 32 - 10][(y + 32) / 32 - 1] != 1) {
                    shape[2][j] = 1;
                    shape[i][j] = 0;
                    board[x / 32 - 10][y / 32 - 1] = 1;
                } else if(shape[i][j] == 1 && shape[1][j] == 0 && board[x / 32 - 10][(y + 32) / 32 - 1] != 1) {
                    shape[1][j] = 1;
                    shape[i][j] = 0;
                    board[x / 32 - 10][y / 32 - 1] = 1;
                }
            }
        }
    }
        */

    bool checkUnder() {
        for (int i = 0; i < TETROMINOGRID; ++i) {
            for (int j = 0; j < TETROMINOGRID; ++j) {
                if (shape[i][j] == 0) continue;

                int newY = y + BLOCKSIZE + (i * BLOCKSIZE);
                int newX = x + (j * BLOCKSIZE);

                int row = (newY - OFFSET_Y) / BLOCKSIZE;
                int col = (newX - OFFSET_X) / BLOCKSIZE;

                if (row > BOARDHEIGHT || col < 0 || col > BOARDWIDTH || board[row][col] == 1) {
                    return false;
                }
            }
        }
        return true;
    }

    void hardDrop() {
    // Drop until we hit something or bottom
    while (true) {
        bool canDrop = true;
        for (int i = 0; i < TETROMINOGRID; ++i) {
            for (int j = 0; j < TETROMINOGRID; ++j) {
                if (shape[i][j] == 0) continue;

                int newY = y + (i * BLOCKSIZE);
                int newX = x + (j * BLOCKSIZE);

                int row = (newY - OFFSET_Y) / BLOCKSIZE;
                int col = (newX - OFFSET_X) / BLOCKSIZE;

                if (row >= BOARDHEIGHT || col < 0 || col >= BOARDWIDTH || board[row][col] == 1) {
                    canDrop = false;
                }
            }
        }

        if (!canDrop) break;
        y += BLOCKSIZE;
    }

    // Lock into board
    for (int i = 0; i < TETROMINOGRID; ++i) {
        for (int j = 0; j < TETROMINOGRID; ++j) {
            if (shape[i][j] == 0) continue;

            int row = (y + i * BLOCKSIZE - OFFSET_Y) / BLOCKSIZE - 1;
            int col = (x + j * BLOCKSIZE - OFFSET_X) / BLOCKSIZE;


            // Safety check to avoid crash
            if (row >= 0 && row < BOARDHEIGHT && col >= 0 && col < BOARDWIDTH) {
                board[row][col] = 1;
            }
        }
    }
}
    ////////////////////////////////////////////////

    bool checkCollision(Grid3x3& newShape) {
        for(int i = 0; i < TETROMINOGRID; ++i) {
            for(int j = 0; j < TETROMINOGRID; ++j) {
                if(newShape[i][j] != 0) {
                    int newX = x + j * BLOCKSIZE;
                    int newY = y + i * BLOCKSIZE;
                    int boardX = newX / 32 - 10;
                    int boardY = newY / 32 - 1;
                    if (newX < 320 || newX > 672 || board[boardX][boardY] != 0)
                        return true;
                    }
                }
            }
        return false;
    }

    bool checkWall(int distance) {
        for(int i = 0; i < TETROMINOGRID; ++i) {
            for(int j = 0; j < TETROMINOGRID; ++j) {
                if(shape[i][j] != 0) {
                    int newX = distance + x + j * BLOCKSIZE;
                    int newY = distance + y + i * BLOCKSIZE;
                    if (newX < 320 || newX > 672)
                        return true;
                    }
                }
            }
        return false;
    }
};

typedef struct {
    SDL_Texture* texture;
    SDL_FRect position;
    SDL_FPoint origin;
    bool visible;
} GameObject;

const Grid3x3 L_Block = {{
    {0, 1, 0},
    {0, 1, 0},
    {0, 1, 1}
}};

const Grid3x3 Square_Block = {{
    {1, 1, 0},
    {1, 1, 0},
    {0, 0, 0}
}};

const Grid3x3 T_Block = {{
    {1, 1, 1},
    {0, 1, 0},
    {0, 0, 0}
}};

const Grid3x3 R_Block = {{
    {0, 1, 1},
    {1, 1, 0},
    {0, 0, 0}
}};

void GameObject_Init(GameObject* obj, SDL_Texture* texture, float x, float y, float w, float h, bool visible);

void GameObject_Render(SDL_Renderer* renderer, const GameObject* obj);

void drawTetromino(const Tetromino& tetromino, SDL_Renderer* renderer, SDL_Texture* blockTexture);

void SpawnTetromino(Grid3x3 blockType, int& destIndex, SDL_Texture* texture, int startX, int startY, int blockW, int blockH);



// TODO:
// Check Collision()
// Lock Piece()
