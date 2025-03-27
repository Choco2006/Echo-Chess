#include "play.h"
#include <iostream>

bool isPlaying = false;
SDL_Texture* playBackgroundTexture = nullptr;

void InitPlay(SDL_Renderer* renderer) {
    std::cout << "Dang khoi tao gameplay" << std::endl;

    SDL_Surface* bgSurface = IMG_Load("resources/images/main/play_background.png");
    if (!bgSurface) {
        std::cerr << "Khong the tai background! Loi: " << IMG_GetError() << std::endl;
    } else {
        playBackgroundTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
        SDL_FreeSurface(bgSurface);
    }

    std::cout << "Khoi tao gameplay thanh cong!" << std::endl;
}

void HandlePlayEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_ESCAPE) {
            isPlaying = false;
        }
    }
}

void RenderPlay(SDL_Renderer* renderer) {
    if (isPlaying){
        if (playBackgroundTexture) {
            SDL_RenderCopy(renderer, playBackgroundTexture, NULL, NULL);
        } else {
            std::cerr << "Texture background gameplay bi null!" << std::endl;
        }

        int boardSize = 400;
        int cellSize = boardSize / 8;

        int startX = 50;
        int startY = (720 - boardSize) / 2;

        //ve vien mau den
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_Rect borderRect = {startX - 5, startY - 5, boardSize + 10, boardSize + 10};
        SDL_RenderFillRect(renderer, &borderRect);

        //ve ban co
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                if ((row + col) % 2 == 0) {
                    SDL_SetRenderDrawColor(renderer, 240, 217, 181, 255);
                } else {
                    SDL_SetRenderDrawColor(renderer, 181, 136, 99, 255);
                }

                SDL_Rect cellRect = {startX + col * cellSize, startY + row * cellSize, cellSize, cellSize};
                SDL_RenderFillRect(renderer, &cellRect);
            }
        }
    }
}

void CleanupPlay() {
    if (playBackgroundTexture) {
        SDL_DestroyTexture(playBackgroundTexture);
        playBackgroundTexture = nullptr;
    }
    std::cout << "Da don dep tai nguyen gameplay" << std::endl;
}