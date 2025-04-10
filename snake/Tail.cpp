//
// Created by r.bauernfeind on 09.04.2025.
//

#include "Tail.h"

#include "GlobalState.h"

void Tail::draw() const {
    SDL_SetRenderDrawColor(gState.renderer, color.r, color.g, color.b, color.a);

    const SDL_FRect tail = {(float) x, (float) y, 50, 50};
    SDL_RenderFillRect(gState.renderer, &tail);
}

void Tail::move(int nextX, int nextY) {
    x = nextX;
    y = nextY;
}
