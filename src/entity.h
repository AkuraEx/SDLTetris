#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <array>
#include <iostream>
#include "texture.h"
#include <random>
#include "definitions.h"

// Unique structure for board information
typedef struct {
    SDL_Texture *texture;
    int fill;
} Tile;

// Each piece uses a grid for matrix transformations
using Grid3x3 = std::array<std::array<int, TETROMINOGRID>, TETROMINOGRID>;
extern Tile board[BOARDHEIGHT][BOARDWIDTH];

// Player actions and collision logic for each block
struct Tetromino {
    Grid3x3 shape;
    int x, y;
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
        } else {
            // Check if collision on both right and left and adjust accordingly
            while(checkCollision(rotated)) {
                if(!checkWall(-BLOCKSIZE)) {
                    x -= 32;
                    shape = rotated;
                } else if(!checkWall(BLOCKSIZE)) {
                    x += 32;
                    shape = rotated;
                } else {
                    return;
                }
            }
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
        } else {
            // Check if collision on both right and left and adjust accordingly
            while(checkCollision(rotated)) {
                if(!checkWall(-BLOCKSIZE)) {
                    x -= 32;
                    shape = rotated;
                } else if(!checkWall(BLOCKSIZE)) {
                    x += 32;
                    shape = rotated;
                } else {
                    return;
                }
            }
        }
    }

    void menuRotateClockwise() {
        Grid3x3 rotated{};
        for (int i = 0; i < TETROMINOGRID; ++i) {
            for (int j = 0; j < TETROMINOGRID; ++j) {
                rotated[j][TETROMINOGRID - 1 - i] = shape[i][j];

            }
        }

        shape = rotated;
    }


    bool checkUnder() {
        for (int i = 0; i < TETROMINOGRID; ++i) {
            for (int j = 0; j < TETROMINOGRID; ++j) {
                if (shape[i][j] == 0) continue;

                int newY = y + BLOCKSIZE + (i * BLOCKSIZE);
                int newX = x + (j * BLOCKSIZE);

                int row = (newY - OFFSET_Y) / BLOCKSIZE;
                int col = (newX - OFFSET_X) / BLOCKSIZE;

                if (row > BOARDHEIGHT || col < 0 || col > BOARDWIDTH || board[row - 1][col].fill == 1) {
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

                if (row >= BOARDHEIGHT || col < 0 || col > BOARDWIDTH || board[row][col].fill == 1) {
                    canDrop = false;
                }
            }
        }

        if (!canDrop) break;
        y += BLOCKSIZE;
        }
    }

    // Lock into board
    void lock() {
    for (int i = 0; i < TETROMINOGRID; ++i) {
        for (int j = 0; j < TETROMINOGRID; ++j) {
            if (shape[i][j] == 0) continue;

            int row = (y + i * BLOCKSIZE - OFFSET_Y) / BLOCKSIZE - 1;
            int col = (x + j * BLOCKSIZE - OFFSET_X) / BLOCKSIZE;


            // Safety check to avoid crash
            if (row >= 0 && row < BOARDHEIGHT && col >= 0 && col < BOARDWIDTH) {
                board[row][col].fill = 1;
                board[row][col].texture = texture;
                }
            }
        }
    }

    bool checkCollision(Grid3x3& newShape) {
        for(int i = 0; i < TETROMINOGRID; ++i) {
            for(int j = 0; j < TETROMINOGRID; ++j) {
                if(newShape[i][j] != 0) {
                    int newX = x + j * BLOCKSIZE;
                    int newY = y + i * BLOCKSIZE;
                    int boardX = newX / 32 - 10;
                    int boardY = newY / 32 - 1;
                    if (newX < 304 || newX > 608 || board[boardY][boardX].fill != 0)
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
                    int boardX = newX / 32 - 10;
                    int boardY = newY / 32;
                    if (newX <= 304 || newX > 608 || board[boardY][boardX].fill != 0) 
                        return true;
                    }
                }
            }
        return false;
    }
};


const Grid3x3 L_Block = {{
    {0, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 1},
    {0, 0, 0, 0}
}};

const Grid3x3 Square_Block = {{
    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}
}};

const Grid3x3 T_Block = {{
    {0, 0, 0, 0},
    {0, 1, 1, 1},
    {0, 0, 1, 0},
    {0, 0, 0, 0}
}};

const Grid3x3 R_Block = {{
    {0, 0, 0, 0},
    {0, 0, 1, 1},
    {0, 1, 1, 0},
    {0, 0, 0, 0}
}};

const Grid3x3 Long_Block = {{
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 0, 0}
}};

const Grid3x3 Left_Block = {{
    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 0}
}};

const Grid3x3 RL_Block = {{
    {0, 0, 0, 0},
    {0, 0, 1, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0}
}};

void drawTetromino(const Tetromino& tetromino, SDL_Renderer* renderer, SDL_Texture* blockTexture);

void SpawnTetromino(Grid3x3 blockType, SDL_Texture* texture, int startX, int startY, int blockW, int blockH);

void renderBoard(SDL_Renderer* renderer);

void clearLine(SDL_Texture* texture, bool& clear, int& cleared, int& Line);

void removeLine(int& cleared, int& Line);

void renderFullFrame();

void randomTetromino(Tetromino& block);

