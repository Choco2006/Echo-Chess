#include "window.h"
#include <SDL2/SDL_image.h>

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 720;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

bool createWindow(){
    window = SDL_CreateWindow(
        "Echo Chess",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (!window){
        std::cout << "Khong the khoi tao cua so! Loi: " << SDL_GetError() << std::endl;
        return false;
    }

    //tai icon
    SDL_Surface* iconSurface = IMG_Load("resources/images/icon/icon.png");
    if (!iconSurface) {
        std::cout << "Khong the tai icon! Loi: " << IMG_GetError() << std::endl;
    } else {
        SDL_SetWindowIcon(window, iconSurface);
        SDL_FreeSurface(iconSurface);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer){
        std::cout << "Khong the render! Loi: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        return false;
    }

    return true;
}

void destroyWindow(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}