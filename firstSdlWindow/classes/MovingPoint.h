//
// Created by r.bauernfeind on 27.03.2025.
//

#ifndef MOVINGPOINT_H
#define MOVINGPOINT_H
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>

#include "Vec2D.h"


class MovingPoint {
private:
    Vec2D position;
    Vec2D velocity;
    SDL_Color color;
    float width = 25;
    float height = 25;

    SDL_FRect getRect() const {
        return SDL_FRect{getTranslatedX(), getTranslatedY(), width, height};
    }

public:
    MovingPoint(const Vec2D &position, const Vec2D &velocity, const SDL_Color &color)
        : position(position), velocity(velocity), color(color) {
    }

    MovingPoint(const Vec2D &position, const Vec2D &velocity, const SDL_Color &color, float width,
                float height)
        : position(position), velocity(velocity), color(color), width(width), height(height) {
    }

    float getTranslatedX() const;

    float getTranslatedY() const;

    void draw() const;

    void update(float deltaTime, bool collision = false);

    void handleBoundaryCollision();

    void handlePointCollision(MovingPoint &other);

    bool isColliding(MovingPoint &other) const;
};


#endif //MOVINGPOINT_H
