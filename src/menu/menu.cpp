#include "menu.h"

SDL_Texture* backgroundTexture = nullptr;

//tai anh nen background
bool LoadMenu(SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load("resources/images/background.png");
    if (!surface) {
        std::cerr << "Failed to load background: " << IMG_GetError() << std::endl;
        return false;
    }
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return backgroundTexture != nullptr;
}

//render menu
void RenderMenu(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
}

//cac nut menu
void HandleMenuEvent(SDL_Event& e, bool& isRunning, bool& inMenu) {
    if (e.type == SDL_QUIT) {
        isRunning = false;
    } else if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_RETURN) { // Nhấn Enter để vào game
            inMenu = false;
        } else if (e.key.keysym.sym == SDLK_ESCAPE) { // Nhấn Esc để thoát
            isRunning = false;
        }
    }
}

//giai phong tai nguyen anh background
void CleanupMenu() {
    if (backgroundTexture) {
        SDL_DestroyTexture(backgroundTexture);
        backgroundTexture = nullptr;
    }
}