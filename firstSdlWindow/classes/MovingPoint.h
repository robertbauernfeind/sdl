//
// Created by r.bauernfeind on 27.03.2025.
//

#ifndef MOVINGPOINT_H
#define MOVINGPOINT_H
#include <SDL3/SDL_pixels.h>

#include "Vec2D.h"


class MovingPoint {
private:
    Vec2D position;
    Vec2D velocity;
    SDL_Color color;
    float radius;

public:
    MovingPoint(const Vec2D &position, const Vec2D &velocity, const SDL_Color &color, float radius)
        : position(position), velocity(velocity), color(color), radius(radius) {
    }

    void draw() const;

    void update(float deltaTime);
};


#endif //MOVINGPOINT_H
