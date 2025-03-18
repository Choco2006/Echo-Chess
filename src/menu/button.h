#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

struct Button{
    SDL_Rect rect;
    SDL_Texture* buttonTexture;
    SDL_Texture* hoverTexture;
    bool isHovered;

    Button(int x, int y, int w, int h, SDL_Texture* tex, SDL_Texture* hover_tex);
    void Render(SDL_Renderer* renderer);
    bool HandleEvent(SDL_Event& e);
};

#endif