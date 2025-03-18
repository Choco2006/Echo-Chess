#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <iostream>

extern SDL_Window* window;
extern SDL_Renderer* renderer;

bool createWindow();
void destroyWindow();

#endif