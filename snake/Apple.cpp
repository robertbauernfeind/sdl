//
// Created by r.bauernfeind on 14.04.2025.
//

#include "Apple.h"

#include <SDL3/SDL_render.h>

#include "GlobalState.h"

void Apple::draw() const {
    SDL_SetRenderDrawColor(gState.renderer, color.r, color.g, color.b, color.a);

    float offset = static_cast<float>(gState.baseStep) - static_cast<float>(gState.appleSize);
    if (offset < 0) {
        offset = 0;
    }

    const SDL_FRect head = {
        static_cast<float>(x) + (offset / 2.0f),
        static_cast<float>(y) + (offset / 2.0f),
        static_cast<float>(gState.appleSize),
        static_cast<float>(gState.appleSize)};
    SDL_RenderFillRect(gState.renderer, &head);
}
