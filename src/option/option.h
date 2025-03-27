#ifndef OPTION_H
#define OPTION_H

#include <SDL2/SDL.h>

extern bool isOptionOpen;

bool LoadOption(SDL_Renderer* renderer);

void InitOption(SDL_Renderer* renderer);
void HandleOptionEvent(SDL_Event& e);
void RenderOption(SDL_Renderer* renderer);
void CleanupOption();

#endif
