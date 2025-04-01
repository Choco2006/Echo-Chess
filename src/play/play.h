#ifndef PLAY_H
#define PLAY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "board.h"

extern bool isPlaying;

extern SDL_Texture* playBackgroundTexture;

extern int selectedRow, selectedCol;
extern Piece selectedPiece;

void InitPlay(SDL_Renderer* renderer);
void HandlePlayEvent(SDL_Event& e);
void RenderPlay(SDL_Renderer* renderer);
void CleanupPlay();

#endif