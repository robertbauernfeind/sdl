//
// Created by r.bauernfeind on 27.03.2025.
//

#ifndef VEC2D_H
#define VEC2D_H
#include <cmath>
#include <SDL3/SDL_render.h>

using namespace std;

class Vec2D {
private:
    float x = 0;
    float y = 0;

public:
    Vec2D(): x(0), y(0) {}
    Vec2D(const float x, const float y): x(x), y(y) {
    }

    float getX() const;
    float getY() const;

    Vec2D operator+(const Vec2D &other) const;

    Vec2D operator-(const Vec2D &other) const;

    Vec2D operator*(float scalar) const;

    float length() const;

    Vec2D normalize() const;
};


#endif //VEC2D_H
