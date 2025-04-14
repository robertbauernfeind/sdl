//
// Created by r.bauernfeind on 14.04.2025.
//

#ifndef APPLE_H
#define APPLE_H
#include <SDL3/SDL_pixels.h>


class Apple {
private:
    int x = 300;
    int y = 300;
    SDL_Color color = { 255, 0, 0, 255 };

public:
    Apple(const int x, const int y): x(x), y(y) {}

    void draw() const;
};



#endif //APPLE_H
