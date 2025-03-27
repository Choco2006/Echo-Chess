#include "option.h"
#include "../menu/button.h"
#include <SDL2/SDL_image.h>
#include <iostream>

SDL_Texture* optionBoxTexture = nullptr;
SDL_Texture* closeBoxTexture = nullptr;
Button closeButton(0, 0, 50, 50, nullptr, nullptr);
bool isOptionOpen = false;

void InitOption(SDL_Renderer* renderer) {
    SDL_Surface* optionBoxSurface = IMG_Load("resources/images/option_box/option_box.png");
    SDL_Surface* closeBoxSurface = IMG_Load("resources/images/option_box/close_option_button.png");

    if (!optionBoxSurface || !closeBoxSurface) {
        std::cerr << "Khong the tai UI Option! Loi: " << IMG_GetError() << std::endl;
        return;
    }

    optionBoxTexture = SDL_CreateTextureFromSurface(renderer, optionBoxSurface);
    closeBoxTexture = SDL_CreateTextureFromSurface(renderer, closeBoxSurface);
    SDL_FreeSurface(optionBoxSurface);
    SDL_FreeSurface(closeBoxSurface);

    int boxWidth = 400, boxHeight = 300;
    int boxX = (960 - boxWidth) / 2;
    int boxY = (720 - boxHeight) / 2;

    int closeSize = 40;
    int closeX = boxX + boxWidth - closeSize - 10;
    int closeY = boxY + 10;

    closeButton = Button(closeX, closeY, closeSize, closeSize, closeBoxTexture, nullptr);
}

bool LoadOption(SDL_Renderer* renderer) {
    InitOption(renderer);
    return true;
}


void HandleOptionEvent(SDL_Event& e) {
    if (closeButton.HandleEvent(e)) {
        isOptionOpen = false;
    }
}

void RenderOption(SDL_Renderer* renderer) {
    if (isOptionOpen) {
        SDL_Rect boxRect = {(960 - 400) / 2, (720 - 300) / 2, 400, 300};
        SDL_RenderCopy(renderer, optionBoxTexture, NULL, &boxRect);
        closeButton.Render(renderer);
    }
}

void CleanupOption() {
    SDL_DestroyTexture(optionBoxTexture);
    SDL_DestroyTexture(closeBoxTexture);
}
