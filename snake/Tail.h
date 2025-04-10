//
// Created by r.bauernfeind on 09.04.2025.
//

#ifndef TAIL_H
#define TAIL_H
#include <SDL3/SDL_pixels.h>

#include "Direction.h"


class Tail {
private:
    int x = 300;
    int y = 300;
    Direction direction = Direction::UP;
    SDL_Color color = { 255, 0, 255, 255 };
public:

    Tail() = default;
    Tail(const int x, const int y): x(x), y(y) {}

    void draw() const;
    void move(int nextX, int nextY);

    int getX() const { return x; }
    int getY() const { return y; }
    void setDirection(const Direction dir) { direction = dir; }
    Direction getDirection() const { return direction; }
};



#endif //TAIL_H
