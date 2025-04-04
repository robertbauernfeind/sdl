//
// Created by r.bauernfeind on 02.04.2025.
//

#include "Head.h"

#include "GlobalState.h"

void Head::draw() const {
    SDL_SetRenderDrawColor(gState.renderer, 255, 50, 50, 255);

    const SDL_FRect head = { (float)x, (float)y, 50, 50 };
    SDL_RenderFillRect(gState.renderer, &head);
}

void Head::changeDirection(const Direction dir) {
    direction = dir;
}

void Head::move() {
    const int step = 50;
    switch (direction) {
        case Direction::UP:
            y -= step;
            break;
        case Direction::DOWN:
            y += step;
            break;
        case Direction::LEFT:
            x -= step;
            break;
        case Direction::RIGHT:
            x += step;
            break;
        default:
            break;
    }
}
