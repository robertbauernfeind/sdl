//
// Created by r.bauernfeind on 27.03.2025.
//

#ifndef GLOBALSTATE_H
#define GLOBALSTATE_H
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>


struct GlobalState {
    SDL_Window *window;
    SDL_Renderer *renderer;
    int width = 800;
    int height = 800;

    int baseStep = 50;
    int headSize = 40;
    int tailSize = 40;
};

extern GlobalState gState;


#endif //GLOBALSTATE_H
