//
// Created by r.bauernfeind on 14.04.2025.
//

#include "Apple.h"

#include <SDL3/SDL_render.h>

#include "GlobalState.h"

void Apple::draw() const {
    SDL_SetRenderDrawColor(gState.renderer, color.r, color.g, color.b, color.a);

    float offset = (float)gState.baseStep - (float)gState.appleSize;
    if (offset < 0) {
        offset = 0;
    }

    const SDL_FRect head = {
        (float) x + (offset / 2.0f),
        (float) y + (offset / 2.0f),
        (float)gState.appleSize,
        (float)gState.appleSize};
    SDL_RenderFillRect(gState.renderer, &head);
}
