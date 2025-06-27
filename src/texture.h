#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

extern SDL_Texture *L_texture, *L_textureA;
extern SDL_Texture *T_texture, *T_textureA;
extern SDL_Texture *Square_texture, *Square_textureA;
extern SDL_Texture *R_texture, *R_textureA;
extern SDL_Texture *Long_texture, *Long_textureA;
extern SDL_Texture *Left_texture, *Left_textureA;
extern SDL_Texture *RL_texture, *RL_textureA;
extern SDL_Texture *Grid_texture;
extern SDL_Texture *Next_texture;
extern SDL_Texture *Hold_texture;
extern SDL_Texture *White_texture;
extern SDL_Texture *Background_texture;
extern SDL_Texture *Numbers_texture;
extern SDL_Texture *Score_texture;
extern SDL_Texture *Level_texture;
extern SDL_Texture *Lines_texture;
extern SDL_Texture *Logo_texture;
extern SDL_Texture *Credits_texture;
extern SDL_Texture *Game_over_texture;
extern SDL_FRect background_position;
extern SDL_FRect grid_position;
extern SDL_FRect next_position;
extern SDL_FRect hold_position;
extern SDL_FRect score_position;
extern SDL_FRect level_position;
extern SDL_FRect lines_position;
extern SDL_FRect logo_position;
extern SDL_FRect credits_position;

SDL_Texture* getTransparentTexture(SDL_Texture* tex);
bool loadTextures(SDL_Renderer* renderer);
void destroyTextures();
