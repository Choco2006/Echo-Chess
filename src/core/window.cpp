#include "window.h"

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 720;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

bool createWindow(){
    std::cout << "Dang khoi tao cua so..." << std::endl;
    window = SDL_CreateWindow(
        "Echo Chess",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (!window){
        std::cout << "Khong the khoi tao cua so! Loi: " << SDL_GetError() << std::endl;
        return false;
    } else {
        std::cout << "Khoi tao cua so thanh cong!" << std::endl;
    }

    std::cout << "Dang render..." << std::endl;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer){
        std::cout << "Khong the render! Loi: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        return false;
    } else {
        std::cout << "Render thanh cong!" << std::endl;
    }

    return true;
}

void destroyWindow(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}