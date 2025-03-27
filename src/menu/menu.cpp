#include "menu.h"
#include "../src/core/init.h"
#include "../src/option/option.h"

SDL_Texture* backgroundTexture = nullptr;
Mix_Music* bgMusic = nullptr;
std::vector<Button> menuButtons;

//tai anh nen background
bool LoadMenu(SDL_Renderer* renderer) {
    std::cout << "Dang tai menu" << std::endl;

    //load background
    SDL_Surface* surface = IMG_Load("resources/images/background.png");
    if (!surface) {
        std::cerr << "Khong the tai duoc hinh nen! Loi: " << IMG_GetError() << std::endl;
        return false;
    }
    std::cout << "Tai anh nen thanh cong!" << std::endl;
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!backgroundTexture) return false;

    //load music
    std::cout << "Dang load nhac nen..." << std::endl;
    bgMusic = Mix_LoadMUS("resources/sound/bg_music.mp3");
    if (!bgMusic) {
        std::cerr << "Khong the load nhac nen! Loi: " << Mix_GetError() << std::endl;
        return false;
    } else {
        std::cout << "Tai nhac nen thanh cong!" << std::endl;
    }
    Mix_PlayMusic(bgMusic, -1);

    //load texture cho nut
    //nut play
    SDL_Surface* playSurface = IMG_Load("resources/images/button/play_button.png");
    SDL_Surface* playHoverSurface = IMG_Load("resources/images/button/play_button_hover.png");

    //nut load game
    SDL_Surface* loadSurface = IMG_Load("resources/images/button/load_button.png");
    SDL_Surface* loadHoverSurface = IMG_Load("resources/images/button/load_button_hover.png");

    //nut option
    SDL_Surface* optionSurface = IMG_Load("resources/images/button/option_button.png");
    SDL_Surface* optionHoverSurface = IMG_Load("resources/images/button/option_button_hover.png");

    //nut exit
    SDL_Surface* exitSurface = IMG_Load("resources/images/button/exit_button.png");
    SDL_Surface* exitHoverSurface = IMG_Load("resources/images/button/exit_button_hover.png");

    if (!playSurface || !playHoverSurface || !exitSurface || !exitHoverSurface ||
    !loadSurface || !loadHoverSurface || !optionSurface || !optionHoverSurface) {
        std::cerr << "Khong the tai duoc hinh anh nut! Loi: " << IMG_GetError() << std::endl;
        return false;
    }

    //texture nut play
    SDL_Texture* playTexture = SDL_CreateTextureFromSurface(renderer, playSurface);
    SDL_Texture* playHoverTexture = SDL_CreateTextureFromSurface(renderer, playHoverSurface);

    //texture nut load game
    SDL_Texture* loadTexture = SDL_CreateTextureFromSurface(renderer, loadSurface);
    SDL_Texture* loadHoverTexture = SDL_CreateTextureFromSurface(renderer, loadHoverSurface);

    //texture nut option
    SDL_Texture* optionTexture = SDL_CreateTextureFromSurface(renderer, optionSurface);
    SDL_Texture* optionHoverTexture = SDL_CreateTextureFromSurface(renderer, optionHoverSurface);

    //texture nut exit
    SDL_Texture* exitTexture = SDL_CreateTextureFromSurface(renderer, exitSurface);
    SDL_Texture* exitHoverTexture = SDL_CreateTextureFromSurface(renderer, exitHoverSurface);

    //free surface nut play
    SDL_FreeSurface(playSurface);
    SDL_FreeSurface(playHoverSurface);

    //free surface nut load
    SDL_FreeSurface(loadSurface);
    SDL_FreeSurface(loadHoverSurface);

    //free surface nut option
    SDL_FreeSurface(optionSurface);
    SDL_FreeSurface(optionHoverSurface);

    //free surface nut exit
    SDL_FreeSurface(exitSurface);
    SDL_FreeSurface(exitHoverSurface);

    //tao cac nut
    menuButtons.push_back(Button((960 - 200)/2, 250, 200, 50, playTexture, playHoverTexture));  //"play"
    menuButtons.push_back(Button((960 - 200)/2, 330, 200, 50, loadTexture, loadHoverTexture));  //"load"
    menuButtons.push_back(Button((960 - 200)/2, 410, 200, 50, optionTexture, optionHoverTexture));  //"option"
    menuButtons.push_back(Button((960 - 200)/2, 490, 200, 50, exitTexture, exitHoverTexture));  // "exit"

    // Tải option menu
    if (!LoadOption(renderer)) {
        std::cerr << "Không thể tải Option Menu!" << std::endl;
        return false;
    }

    //phan return ham bool gốc
    return true; 
}

//render menu
void RenderMenu(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    for (auto& button : menuButtons) {
        button.Render(renderer);
    }
    if (isOptionOpen) {
        RenderOption(renderer);
    }
}

//cac nut menu
void HandleMenuEvent(SDL_Event& e, bool& isRunning, bool& inMenu){
    if (e.type == SDL_QUIT){
        isRunning = false;
    }

    //nut play
    if (menuButtons[0].HandleEvent(e)){
        std::cout << "Bat dau tro choi moi!" << std::endl;
        inMenu = false;
    }

    //nut"option"
    if (menuButtons[2].HandleEvent(e)) { 
        isOptionOpen = true; 
    }
    if (isOptionOpen) {
        HandleOptionEvent(e);
    }

    //nut "exit"
    if (menuButtons[3].HandleEvent(e)){
        std::cout << "Thoat game!" << std::endl;
        isRunning = false;
    }
}

//giai phong tai nguyen
void CleanupMenu(){
    if (backgroundTexture){
        SDL_DestroyTexture(backgroundTexture);
        backgroundTexture = nullptr;
    }
    if (bgMusic){
        Mix_FreeMusic(bgMusic);
        bgMusic = nullptr;
    }
    CleanupOption();
}