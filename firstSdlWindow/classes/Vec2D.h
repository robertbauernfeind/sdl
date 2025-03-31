//
// Created by r.bauernfeind on 27.03.2025.
//

#ifndef VEC2D_H
#define VEC2D_H
#include <cmath>

using namespace std;

class Vec2D {
private:
    float x = 0;
    float y = 0;

public:
    Vec2D(): x(0), y(0) {
    }

    Vec2D(const float x, const float y): x(x), y(y) {
    }

    float getX() const;

    void setX(float x);

    float getY() const;

    void setY(float y);

    Vec2D operator+(const Vec2D &other) const;

    Vec2D operator-(const Vec2D &other) const;

    Vec2D operator*(float scalar) const;

    Vec2D &operator+=(const Vec2D &other);

    Vec2D &operator-=(const Vec2D &other);

    float length() const;

    Vec2D normalize() const;

    float dot(const Vec2D &other) const;
};


#endif //VEC2D_H
