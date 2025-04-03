//
// Created by r.bauernfeind on 02.04.2025.
//

#ifndef HEAD_H
#define HEAD_H
#include <SDL3/SDL_render.h>

enum class Direction {
    UP = 1,
    DOWN = 2,
    LEFT = 3,
    RIGHT = 4
};

class Head {
private:
    int x = 300;
    int y = 300;
    Direction direction = Direction::UP;

public:
    void draw(SDL_Renderer* renderer) const;
    void changeDirection(Direction dir);
    void move();
};


#endif //HEAD_H
