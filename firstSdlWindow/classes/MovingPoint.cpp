//
// Created by r.bauernfeind on 27.03.2025.
//

#include "MovingPoint.h"
#include "GlobalState.h"

void MovingPoint::draw() const {
    SDL_SetRenderDrawColor(gState.renderer, color.r, color.g, color.b, color.a);
    const SDL_FRect rectangle{position.getX(), position.getY(), 25, 25};

    SDL_RenderFillRect(gState.renderer, &rectangle);
}

void MovingPoint::update(const float deltaTime) {
    position = position + (velocity * deltaTime);
}
