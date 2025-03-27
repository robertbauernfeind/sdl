//
// Created by r.bauernfeind on 27.03.2025.
//

#include "Vec2D.h"

#include <SDL3/SDL_render.h>

float Vec2D::getX() const {
    return x;
}

float Vec2D::getY() const {
    return y;
}

Vec2D Vec2D::operator+(const Vec2D &other) const {
    return Vec2D{x + other.x, y + other.y};
}

Vec2D Vec2D::operator-(const Vec2D &other) const {
    return Vec2D{x - other.x, y - other.y};
}

Vec2D Vec2D::operator*(float scalar) const {
    return Vec2D{x * scalar, y * scalar};
}

float Vec2D::length() const {
    return sqrt(x * x + y * y);
}

Vec2D Vec2D::normalize() const {
    float l = length();
    return Vec2D{x / l, y / l};
}
