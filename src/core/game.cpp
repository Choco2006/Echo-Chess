#include "game.h"
#include "window.h"
#include "../src/menu/menu.h"
#include "../src/option/option.h"
#include "../play/play.h"

void runGame(){

    bool isRunning = true;
    bool isMenu = true;
    SDL_Event event;

    //load menu
    if (!LoadMenu(renderer)){
        std::cerr << "Khong load duoc menu!" << std::endl;
        isRunning = false;
    }

    // Load Option UI
    if (!LoadOption(renderer)) {
        std::cerr << "Không load duoc option!" << std::endl;
        isRunning = false;
    }
    
    while (isRunning){
        SDL_RenderClear(renderer);

        while (SDL_PollEvent(&event) != 0) {
            if (isMenu) {
                HandleMenuEvent(event, isRunning, isMenu);
            } else {
                HandlePlayEvent(event);
                
                if (event.type == SDL_QUIT) {
                    isRunning = false;
                }
            }
        }

        if (isMenu){
            RenderMenu(renderer);
        } else {
            if (!isPlaying){
                isPlaying = true;
                InitPlay(renderer);
            }
            RenderPlay(renderer);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    CleanupMenu();
    CleanupOption();
    CleanupPlay();
}