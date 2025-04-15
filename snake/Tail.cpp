//
// Created by r.bauernfeind on 09.04.2025.
//

#include "Tail.h"

#include "GlobalState.h"

void Tail::draw() const {
    SDL_SetRenderDrawColor(gState.renderer, color.r, color.g, color.b, color.a);

    float offset = static_cast<float>(gState.baseStep) - static_cast<float>(gState.tailSize);
    if (offset < 0) {
        offset = 0;
    }

    const SDL_FRect tail = {
        static_cast<float>(x) + (offset / 2.0f),
        static_cast<float>(y) + (offset / 2.0f),
        static_cast<float>(gState.tailSize),
        static_cast<float>(gState.tailSize)};

    SDL_RenderFillRect(gState.renderer, &tail);
}

void Tail::move(const int nextX, const int nextY) {
    x = nextX;
    y = nextY;
}
