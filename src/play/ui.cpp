#include "ui.h"
#include "../core/init.h"
#include <iostream>

std::vector<MoveRecord> whiteMoves;
std::vector<MoveRecord> blackMoves;

SDL_Texture* uiBackground = nullptr;
SDL_Rect uiRect = {550, 160, 360, 400};
int scrollOffset = 0;
TTF_Font* font = nullptr;
SDL_Color textColor = {0, 0, 0, 255};

void InitUI(SDL_Renderer* renderer) {
    //load font
    font = TTF_OpenFont("resources/fonts/000 Comic Sans TB.ttf", 20);
    if (!font) {
        std::cerr << "Khong the load font! Loi: " << TTF_GetError() << std::endl;
        return;
    }

    //tao background ui
    uiBackground = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 360, 400);
    SDL_SetRenderTarget(renderer, uiBackground);
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, NULL);
}

void AddMove(const std::string& move, bool isWhite) {
    if (isWhite) {
        whiteMoves.push_back({move});
    } else {
        blackMoves.push_back({move});
    }
}

void HandleUIEvent(SDL_Event& e) {
    if (e.type == SDL_MOUSEWHEEL) {
        if (e.wheel.y > 0) {
            scrollOffset -= 20;
        } else if (e.wheel.y < 0) {
            scrollOffset += 20;
        }
        if (scrollOffset < 0) scrollOffset = 0;
    }
}

void RenderUI(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, uiBackground, NULL, &uiRect);

    //vien ui
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &uiRect);

    //dau gach den doc giua
    SDL_RenderDrawLine(renderer, uiRect.x + uiRect.w / 2, uiRect.y, uiRect.x + uiRect.w / 2, uiRect.y + uiRect.h);

    //render chu white va black
    SDL_Surface* whiteSurface = TTF_RenderText_Solid(font, "White", textColor);
    SDL_Surface* blackSurface = TTF_RenderText_Solid(font, "Black", textColor);
    
    int titleY = uiRect.y + 10;
    int lineY = titleY + 25;

    if (whiteSurface && blackSurface) {
        SDL_Texture* whiteTexture = SDL_CreateTextureFromSurface(renderer, whiteSurface);
        SDL_Texture* blackTexture = SDL_CreateTextureFromSurface(renderer, blackSurface);
        
        SDL_Rect whiteRect = {uiRect.x + uiRect.w / 4 - whiteSurface->w / 2, titleY, whiteSurface->w, whiteSurface->h};
        SDL_Rect blackRect = {uiRect.x + (uiRect.w * 3 / 4) - blackSurface->w / 2, titleY, blackSurface->w, blackSurface->h};

        SDL_RenderCopy(renderer, whiteTexture, NULL, &whiteRect);
        SDL_RenderCopy(renderer, blackTexture, NULL, &blackRect);

        SDL_FreeSurface(whiteSurface);
        SDL_FreeSurface(blackSurface);
        SDL_DestroyTexture(whiteTexture);
        SDL_DestroyTexture(blackTexture);
    }

    //gach ngang duoi white va black
    SDL_RenderDrawLine(renderer, uiRect.x, lineY, uiRect.x + uiRect.w, lineY);

    //ve nuoc di
    int y = lineY + 10 - scrollOffset;
    for (size_t i = 0; i < whiteMoves.size(); ++i) {
        SDL_Surface* whiteMoveSurface = TTF_RenderText_Solid(font, whiteMoves[i].move.c_str(), textColor);
        SDL_Surface* blackMoveSurface = (i < blackMoves.size()) ? TTF_RenderText_Solid(font, blackMoves[i].move.c_str(), textColor) : nullptr;

        if (whiteMoveSurface) {
            SDL_Texture* whiteMoveTexture = SDL_CreateTextureFromSurface(renderer, whiteMoveSurface);
            SDL_Rect whiteMoveRect = {uiRect.x + uiRect.w / 4 - whiteMoveSurface->w / 2, y, whiteMoveSurface->w, whiteMoveSurface->h};
            SDL_RenderCopy(renderer, whiteMoveTexture, NULL, &whiteMoveRect);

            SDL_FreeSurface(whiteMoveSurface);
            SDL_DestroyTexture(whiteMoveTexture);
        }

        if (blackMoveSurface) {
            SDL_Texture* blackMoveTexture = SDL_CreateTextureFromSurface(renderer, blackMoveSurface);
            SDL_Rect blackMoveRect = {uiRect.x + (uiRect.w * 3 / 4) - blackMoveSurface->w / 2, y, blackMoveSurface->w, blackMoveSurface->h};
            SDL_RenderCopy(renderer, blackMoveTexture, NULL, &blackMoveRect);

            SDL_FreeSurface(blackMoveSurface);
            SDL_DestroyTexture(blackMoveTexture);
        }

        y += 25;
    }
}

void CleanupUI() {
    SDL_DestroyTexture(uiBackground);
    if (font) {
        TTF_CloseFont(font);
    }
    TTF_Quit();
}
