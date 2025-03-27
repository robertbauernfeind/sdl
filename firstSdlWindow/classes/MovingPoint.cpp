//
// Created by r.bauernfeind on 27.03.2025.
//

#include "MovingPoint.h"
#include "GlobalState.h"

void MovingPoint::draw() const {
    SDL_SetRenderDrawColor(gState.renderer, color.r, color.g, color.b, color.a);
    const SDL_FRect rectangle{position.getX() - (width / 2) , position.getY() + (height / 2), width, height};

    SDL_RenderFillRect(gState.renderer, &rectangle);
}

void MovingPoint::update(const float deltaTime, bool collision) {
    position = position + (velocity * deltaTime);
    if (collision) {
        handleBoundaryCollision();
    }
}

void MovingPoint::handleBoundaryCollision() {
    if (position.getX() < 0 || position.getX() > static_cast<float>(gState.width)) {
        velocity = Vec2D{-velocity.getX(), velocity.getY()};
    }

    if (position.getY() < 0 || position.getY() > static_cast<float>(gState.height)) {
        velocity = Vec2D{velocity.getX(), -velocity.getY()};
    }
}

void MovingPoint::handlePointCollision(const MovingPoint &other) {
    if (other.position.getX() - position.getX() < 25 && other.position.getY() - position.getY() < 25) {
        velocity = Vec2D{-velocity.getX(), -velocity.getY()};
    }
}
