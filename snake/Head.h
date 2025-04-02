//
// Created by r.bauernfeind on 02.04.2025.
//

#ifndef HEAD_H
#define HEAD_H
#include <SDL3/SDL_render.h>


class Head {
private:
    int x = 300;
    int y = 300;
public:
    void draw(SDL_Renderer* renderer) const;
    void move(int direction);
};


#endif //HEAD_H
