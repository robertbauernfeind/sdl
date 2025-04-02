//
// Created by r.bauernfeind on 02.04.2025.
//

#include "Head.h"

void Head::draw(SDL_Renderer *renderer) const {
    SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);

    SDL_FRect head = { (float)x, (float)y, 50, 50 };
    SDL_RenderFillRect(renderer, &head);
}

void Head::move(int direction) {
    int step = 50;
    switch (direction) {
        case 0: // up
            y -= step;
            break;
        case 1: // down
            y += step;
            break;
        case 2: // left
            x -= step;
            break;
        case 3: // right
            x += step;
            break;
        default:
            break;
    }
}
