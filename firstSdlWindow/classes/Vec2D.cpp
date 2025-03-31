//
// Created by r.bauernfeind on 27.03.2025.
//

#include "Vec2D.h"

#include <SDL3/SDL_render.h>

float Vec2D::getX() const {
    return x;
}

void Vec2D::setX(float x) {
    Vec2D::x = x;
}

float Vec2D::getY() const {
    return y;
}

void Vec2D::setY(float y) {
    Vec2D::y = y;
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

Vec2D &Vec2D::operator+=(const Vec2D &other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vec2D &Vec2D::operator-=(const Vec2D &other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

float Vec2D::length() const {
    return sqrt(x * x + y * y);
}

Vec2D Vec2D::normalize() const {
    float l = length();
    return Vec2D{x / l, y / l};
}

float Vec2D::dot(const Vec2D &other) const {
    return x * other.x + y * other.y;
}
