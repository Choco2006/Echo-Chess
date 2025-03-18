#include "init.h"
#include "window.h"

bool InitSDL(){
    std::cout << "Dang khoi tao SDL..." << std::endl;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "Khoi tao SDL that bai! Loi: " << SDL_GetError() << std::endl;
        return false;
    } else {
        std::cout << "Khoi tao SDL thanh cong!" << std::endl;
    }
    
    if (!createWindow()){
        return false;
    }

    return true;
}

void close(){
    destroyWindow();
    SDL_Quit();
}