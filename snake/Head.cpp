//
// Created by r.bauernfeind on 02.04.2025.
//

#include "Head.h"

#include "GlobalState.h"

void Head::draw() const {
    SDL_SetRenderDrawColor(gState.renderer, color.r, color.g, color.b, color.a);

    const SDL_FRect head = {(float) x, (float) y, 50, 50};
    SDL_RenderFillRect(gState.renderer, &head);
}

void Head::changeDirection(const Direction dir) {
    direction = dir;
}

void Head::move() {
    const int step = 50;
    int newX = x;
    int newY = y;
    switch (direction) {
        case Direction::UP:
            newY = y - step;

            if (newY < 0) {
                newY = gState.height - step;
            }
            break;
        case Direction::DOWN:
            newY = y + step;

            if (newY > gState.height - step) {
                newY = 0;
            }
            break;
        case Direction::LEFT:
            newX = x - step;

            if (newX < 0) {
                newX = gState.width - step;
            }
            break;
        case Direction::RIGHT:
            newX = x + step;

            if (newX > gState.width - step) {
                newX = 0;
            }
            break;
        default:
            break;
    }

    y = newY;
    x = newX;
}
