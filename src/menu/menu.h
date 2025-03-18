#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

extern SDL_Texture* backgroundTexture;

bool LoadMenu(SDL_Renderer* renderer);
void RenderMenu(SDL_Renderer* renderer);
void HandleMenuEvent(SDL_Event& e, bool& isRunning, bool& inMenu);
void CleanupMenu();

#endif