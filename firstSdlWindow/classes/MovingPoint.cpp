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
    checkBoundaryCollision();
}

bool MovingPoint::checkBoundaryCollision() {
    if (position.getX() < 0 || position.getX() > static_cast<float>(gState.width)) {
        velocity = Vec2D{-velocity.getX(), velocity.getY()};
        return true;
    }

    if (position.getY() < 0 || position.getY() > static_cast<float>(gState.height)) {
        velocity = Vec2D{velocity.getX(), -velocity.getY()};
        return true;
    }

    return false;
}
