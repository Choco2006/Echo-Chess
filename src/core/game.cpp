#include "game.h"
#include "window.h"

void runGame(){

    bool isRunning = true;
    SDL_Event event;

    while (isRunning){
        //clear man hinh
        SDL_RenderClear(renderer);

        while (SDL_PollEvent(&event) != 0){
            if (event.type == SDL_QUIT){
                isRunning = false;
            }
        }

        SDL_Delay(16);
        
    }
}