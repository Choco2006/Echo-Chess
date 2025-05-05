#include "init.h"
#include "window.h"

bool InitSDL(){
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0){
        std::cerr << "[ERROR] Khoi tao SDL that bai! Loi: " << SDL_GetError() << std::endl;
        return false;
    }

    if (!createWindow()) {
        return false;
    }

    //khoi tao sdl mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "[ERROR] Khong the khoi tao SDL Mixer! Loi: " << Mix_GetError() << std::endl;
        return false;
    }

    //khoi tao sdl image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "[ERROR] Khoi tao SDL_image that bai! Loi: " << IMG_GetError() << std::endl;
        return false;
    }

    //khoi tao sdl ttf
    if (TTF_Init() == -1) {
        std::cout << "[ERROR] Khoi tao TTF that bai! Loi: " << TTF_GetError() << std::endl;
        return false;
    }
    return true;
}

void close(){
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    destroyWindow();
    SDL_Quit();
}
