//
// Created by r.bauernfeind on 27.03.2025.
//

#ifndef GLOBALSTATE_H
#define GLOBALSTATE_H
#include <vector>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

#include "Apple.h"
#include "Head.h"


struct GlobalState {
    // window
    SDL_Window *window;
    SDL_Renderer *renderer;
    int width = 800;
    int height = 800;

    // game settings
    int baseStep = 50;
    int headSize = 40;
    int tailSize = 40;
    int appleSize = 40;

    // game state
    Head snake;
    std::vector<Apple> apples;
};

extern GlobalState gState;


#endif //GLOBALSTATE_H
