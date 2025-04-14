//
// Created by r.bauernfeind on 02.04.2025.
//

#ifndef HEAD_H
#define HEAD_H
#include <vector>
#include <SDL3/SDL_render.h>

#include "Direction.h"
#include "Tail.h"

class Head {
private:
    int x = 300;
    int y = 300;
    Direction direction = Direction::UP;
    SDL_Color color = { 255, 255, 0, 255 };
    std::vector<Tail> tails;

public:
    void draw() const;
    void changeDirection(Direction dir);
    void move();
    void addTail();
    bool collidesWithApple();
};


#endif //HEAD_H
