//
// Created by r.bauernfeind on 09.04.2025.
//

#include "Tail.h"

#include "GlobalState.h"

void Tail::draw() const {
    SDL_SetRenderDrawColor(gState.renderer, color.r, color.g, color.b, color.a);

    float offset = (float)gState.baseStep - (float)gState.tailSize;
    if (offset < 0) {
        offset = 0;
    }

    const SDL_FRect tail = {
        (float) x + (offset / 2.0f),
        (float) y - (offset / 2.0f),
        (float)gState.tailSize,
        (float)gState.tailSize};

    SDL_RenderFillRect(gState.renderer, &tail);
}

void Tail::move(int nextX, int nextY) {
    x = nextX;
    y = nextY;
}
