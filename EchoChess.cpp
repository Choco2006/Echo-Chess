#include "../src/core/init.h"
#include "../src/core/game.h"

int main(int argc, char* argv[]){
    if (!InitSDL()){
        return -1;
    }

    //chay game
    runGame();

    //giai phong tai nguyen
    close();

    return 0;
}