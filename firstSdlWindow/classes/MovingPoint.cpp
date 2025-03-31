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
    if ((getTranslatedX() < 0) || ((getTranslatedX() + width) > static_cast<float>(gState.width))) {
        position.setX(getTranslatedX() < 0 ? width / 2 : static_cast<float>(gState.width) - width / 2);
        velocity = Vec2D{-velocity.getX(), velocity.getY()};
    }

    if ((getTranslatedY()) < 0 || ((getTranslatedY() + height) > static_cast<float>(gState.height))) {
        position.setY(getTranslatedY() < 0 ? height / 2 : static_cast<float>(gState.height) - height / 2);
        velocity = Vec2D{velocity.getX(), -velocity.getY()};
    }
}

bool MovingPoint::isColliding(MovingPoint &other) const {
    SDL_FRect thisRect = this->getRect();
    SDL_FRect otherRect = other.getRect();

    const bool colliding = SDL_HasRectIntersectionFloat(
        &thisRect, &otherRect
    );

    return colliding;
}

void MovingPoint::handlePointCollision(MovingPoint &other) {
    if (!isColliding(other)) return;

    Vec2D collisionNormal = this->position - other.position;

    if (collisionNormal.length() == 0) {
        collisionNormal = Vec2D(1.0f, 0.0f); // Setze eine Standardrichtung
    } else {
        collisionNormal = collisionNormal.normalize();
    }

    Vec2D relativeVelocity = this->velocity - other.velocity;

    if (relativeVelocity.dot(collisionNormal) > 0) return;

    float velocityAlongNormal = relativeVelocity.dot(collisionNormal);

    // Restitutionskoeffizient (1.0 = perfekt elastisch, 0.0 = unelastisch)
    float restitution = 1.0f; // Kann auf 0.8 oder niedriger gesetzt werden für realistischere Kollisionen

    // Impulsberechnung
    float impulseScalar = (2 * velocityAlongNormal) / 2; // Da Massen gleich sind, einfach geteilt durch 2
    Vec2D impulse = collisionNormal * impulseScalar * restitution;

    // Neue Geschwindigkeiten setzen
    this->velocity -= impulse;
    other.velocity += impulse;
}
