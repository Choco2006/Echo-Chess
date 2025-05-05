#include "option.h"
#include "../menu/button.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

SDL_Texture* optionBoxTexture = nullptr;
SDL_Texture* closeBoxTexture = nullptr;
Button closeButton(0, 0, 50, 50, nullptr, nullptr);
bool isOptionOpen = false;
bool isDraggingVolumeSlider = false;
int currentVolume = 50;
SDL_Rect volumeSliderBar;
SDL_Rect volumeSliderHandle;

void InitOption(SDL_Renderer* renderer) {
    SDL_Surface* optionBoxSurface = IMG_Load("resources/images/option_box/option_box.png");
    SDL_Surface* closeBoxSurface = IMG_Load("resources/images/option_box/close_option_button.png");

    if (!optionBoxSurface || !closeBoxSurface) {
        std::cout << "Khong the tai UI Option! Loi: " << IMG_GetError() << std::endl;
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

    //thanh keo am luong
    int sliderBarWidth = 200;
    int sliderBarHeight = 20;
    int sliderBarX = boxX + (boxWidth - sliderBarWidth) / 2;
    int sliderBarY = boxY + boxHeight - 80;
    
    volumeSliderBar = {sliderBarX, sliderBarY, sliderBarWidth, sliderBarHeight};
    
    int sliderHandleWidth = 20;
    int sliderHandleHeight = 30;
    int sliderHandleX = sliderBarX + (currentVolume * sliderBarWidth) / 100 - sliderHandleWidth / 2;
    int sliderHandleY = sliderBarY - (sliderHandleHeight - sliderBarHeight) / 2;
    
    volumeSliderHandle = {sliderHandleX, sliderHandleY, sliderHandleWidth, sliderHandleHeight};
}

bool LoadOption(SDL_Renderer* renderer) {
    InitOption(renderer);
    return true;
}


void HandleOptionEvent(SDL_Event& e) {
    if (closeButton.HandleEvent(e)) {
        isOptionOpen = false;
    }

    //bam chuot
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX = e.button.x;
        int mouseY = e.button.y;

        //check neu chuot nam tren thanh keo am luong
        if (mouseX >= volumeSliderBar.x && mouseX <= volumeSliderBar.x + volumeSliderBar.w &&
            mouseY >= volumeSliderBar.y && mouseY <= volumeSliderBar.y + volumeSliderBar.h) {
            isDraggingVolumeSlider = true;
        }
    }

    //xu ly keo chuot
    if (e.type == SDL_MOUSEMOTION && isDraggingVolumeSlider) {
        int mouseX = e.motion.x;

        //tinh gia tri am luong moi
        currentVolume = ((mouseX - volumeSliderBar.x) * 100) / volumeSliderBar.w;
        if (currentVolume < 0) currentVolume = 0;
        if (currentVolume > 100) currentVolume = 100;

        //cap nhat vi tri thanh keo
        volumeSliderHandle.x = volumeSliderBar.x + (currentVolume * volumeSliderBar.w) / 100 - volumeSliderHandle.w / 2;

        //cap nhat am luong
        Mix_Volume(-1, (MIX_MAX_VOLUME * currentVolume) / 100);
        Mix_VolumeMusic((MIX_MAX_VOLUME * currentVolume) / 100);

        std::cout << "Volume: " << currentVolume << "%" << std::endl;
    }

    //xu ly su kien tha chuot
    if (e.type == SDL_MOUSEBUTTONUP) {
        isDraggingVolumeSlider = false; // Kết thúc kéo thanh
    }
}

void RenderOption(SDL_Renderer* renderer) {
    if (isOptionOpen) {
        SDL_Rect boxRect = {(960 - 400) / 2, (720 - 300) / 2, 400, 300};
        SDL_RenderCopy(renderer, optionBoxTexture, NULL, &boxRect);
        closeButton.Render(renderer);

        //ve thanh keo
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_RenderFillRect(renderer, &volumeSliderBar);
        
        SDL_SetRenderDrawColor(renderer, 0, 128, 255, 255);
        SDL_RenderFillRect(renderer, &volumeSliderHandle);
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &volumeSliderBar);
        SDL_RenderDrawRect(renderer, &volumeSliderHandle);
    }
}

void CleanupOption() {
    SDL_DestroyTexture(optionBoxTexture);
    SDL_DestroyTexture(closeBoxTexture);
}
