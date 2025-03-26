#include <iostream>
#include "SDL3/SDL.h"
// #include <SDL3/SDL_main.h>

using namespace std;

int main() {
    SDL_Log("%s", "Hello World from my first SDL3 project!");

    SDL_Init(SDL_INIT_VIDEO);

    bool done = false;
    SDL_Window *window = SDL_CreateWindow(
        "Hello World!",
        600,
        400,
        SDL_WINDOW_OPENGL);

    if (window == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to create window: %s", SDL_GetError());
        return 1;
    }

    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    done = true;
                    break;
                default:
                    break;
            }
        }

        // do logic here
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
