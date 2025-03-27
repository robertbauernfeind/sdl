//
// Created by r.bauernfeind on 27.03.2025.
//

#include "MovingPoint.h"
#include "GlobalState.h"

float MovingPoint::getTranslatedX() const {
    return position.getX() - (width / 2);
}

float MovingPoint::getTranslatedY() const {
    return position.getY() - (height / 2);
}


void MovingPoint::draw() const {
    SDL_SetRenderDrawColor(gState.renderer, color.r, color.g, color.b, color.a);
    const SDL_FRect rectangle{getTranslatedX(), getTranslatedY(), width, height};

    SDL_RenderFillRect(gState.renderer, &rectangle);

    SDL_SetRenderDrawColor(gState.renderer, 0, 0, 255, 0);

    const SDL_FRect middle{
        position.getX() - (width / 100 * 20) / 2,
        position.getY() - (height / 100 * 20) / 2,
        width / 100 * 20,
        height / 100 * 20
    };
    SDL_RenderFillRect(gState.renderer, &middle);
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

void MovingPoint::handlePointCollision(MovingPoint &other) {
    const auto delta = this->position - other.position;

    float xDiff = abs(delta.getX());
    float yDiff = abs(delta.getY());
    float minDistanceX = (this->width / 2) + (other.width / 2);
    float minDistanceY = (this->height / 2) + (other.height / 2);

    if (xDiff < minDistanceX) {
        velocity = Vec2D{-velocity.getX(), velocity.getY()};
        other.velocity = Vec2D{-other.velocity.getX(), other.velocity.getY()};
    }

    if (yDiff < minDistanceY) {
        velocity = Vec2D{velocity.getX(), -velocity.getY()};
        other.velocity = Vec2D{other.velocity.getX(), -other.velocity.getY()};
    }
}
