#ifndef UI_H
#define UI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>

struct MoveRecord {
    std::string move;
};

void InitUI(SDL_Renderer* renderer);
void RenderUI(SDL_Renderer* renderer);
void HandleUIEvent(SDL_Event& e);
void AddMove(const std::string& move, bool isWhite);
void CleanupUI();

#endif
