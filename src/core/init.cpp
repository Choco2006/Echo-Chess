#include "init.h"
#include "window.h"

bool InitSDL(){
    std::cout << "Dang khoi tao SDL..." << std::endl;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {  // Thêm SDL_INIT_AUDIO
        std::cerr << "Khoi tao SDL that bai! Loi: " << SDL_GetError() << std::endl;
        return false;
    }
    std::cout << "Khoi tao SDL thanh cong!" << std::endl;

    if (!createWindow()) {
        return false;
    }

    //khoi tao sdl mixer
    std::cout << "Dang khoi tao SDL Mixer..." << std::endl;
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Khong the khoi tao SDL Mixer! Loi: " << Mix_GetError() << std::endl;
        return false;
    }
    std::cout << "Khoi tao SDL Mixer thanh cong!" << std::endl;

    //khoi tao sdl image
    std::cout << "Dang khoi tao SDL_image..." << std::endl;
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "Khoi tao SDL_image that bai! Loi: " << IMG_GetError() << std::endl;
        return false;
    }
    std::cout << "Khoi tao SDL_image thanh cong!" << std::endl;

    //khoi tao sdl ttf
    if (TTF_Init() == -1) {
        std::cerr << "Khoi tao TTF that bai! Loi: " << TTF_GetError() << std::endl;
        return false;
    }

    return true;
}

void close(){
    std::cout << "Dang giai phong tai nguyen..." << std::endl;
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    destroyWindow();
    SDL_Quit();
    std::cout << "Da giai phong tai nguyen hoan tat." << std::endl;
}
