#include "button.h"

//ham khoi tao button
Button::Button(int x, int y, int w, int h, SDL_Texture* tex, SDL_Texture* hover_tex){
    rect = {x, y, w, h};
    buttonTexture = tex;
    hoverTexture = hover_tex;
    isHovered = false;
}

//ve nut bam len man hinh
void Button::Render(SDL_Renderer* renderer) {
    if (isHovered) {
        SDL_RenderCopy(renderer, hoverTexture, NULL, &rect);
    } else {
        SDL_RenderCopy(renderer, buttonTexture, NULL, &rect);
    }
}

//click check
bool Button::HandleEvent(SDL_Event& e){
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    
    bool inside = (mouseX >= rect.x && mouseX <= rect.x + rect.w &&
                   mouseY >= rect.y && mouseY <= rect.y + rect.h);

    isHovered = inside;

    if (inside && e.type == SDL_MOUSEBUTTONDOWN){
        return true;
    }
    return false;
}

