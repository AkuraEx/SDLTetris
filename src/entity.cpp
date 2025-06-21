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

void renderBoard(SDL_Renderer* renderer) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            if(board[i][j].fill == 1) {
                SDL_FRect temp;
                temp.x = j * 32 + OFFSET_X;
                temp.y = i * 32 + OFFSET_Y + 32;
                temp.h = 32;
                temp.w = 32;
                SDL_RenderTexture(renderer, board[i][j].texture, NULL, &temp);
            }
        }
    }
}

void clearLine(SDL_Texture* texture, bool& clear, int& cleared, int& Line) {
    bool change = false;
    cleared = 0;
    Line = 0;

    for (int i = BOARDHEIGHT - 1; i >= 0; i--) {
        for (int j = 0; j < BOARDWIDTH; j++) {
            if(board[i][j].fill == 0) {
                break;
            }
            if(j == 9 && board[i][j].fill == 1) {
                if(change == false) {
                    Line = i;
                }
                change = true;
                cleared++;

            }
        }
    }

    if(change) {
        clear = change;
        for (int i = Line; i > Line - cleared; i--) {
            for(int j = 0; j < BOARDWIDTH; j++) {
                board[i][j].texture = texture;
            }
        }
    }
}


void removeLine(int& cleared, int& Line) {

        for (int i = Line; i > Line - cleared; i--) {
            for(int j = 0; j < BOARDWIDTH; j++) {
                board[i][j].fill = 0;
                board[i][j].texture = NULL;
            }
        }
    
        for (int i = Line; i > 0; i--) {
            for (int j = 0; j < BOARDWIDTH; j++) {
                int k = 1;
                int l = 0;
                
                while(l < cleared && i + k >= 0 && board[i + l][j].fill == 1 && board[i + k][j].fill == 0) {
                    board[i + k][j] = board[i + l][j];
                    board[i + l][j].fill = 0;
                    board[i + l][j].texture = NULL;
                    k ++;
                    l ++;
            }
        }
    }
}


void randomTetromino(Tetromino& block) {
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