#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include "definitions.h"
#include "texture.h"

extern int score;

void addScore(int cleared);
void renderScore(SDL_Renderer* renderer);
void renderLevel(SDL_Renderer* renderer, int level, int totalLines);