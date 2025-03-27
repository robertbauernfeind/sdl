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
    int width = 600;
    int height = 800;
};

extern GlobalState gState;


#endif //GLOBALSTATE_H
