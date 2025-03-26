#include <iostream>
#include "SDL3/SDL.h"
// #include <SDL3/SDL_main.h>

using namespace std;

int main() {
    SDL_Log("%s", "Hello World from my first SDL3 project!");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_Init: %s\n", SDL_GetError());
        return 1;
    }

    bool done = false;
    SDL_Window *window;
    SDL_Renderer *renderer;

    if (!SDL_CreateWindowAndRenderer(
        "Hello World",
        800,
        600,
        SDL_WINDOW_OPENGL,
        &window,
        &renderer
    ))

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
        // Clear screen with black
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw red rectangle
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_FRect rect = {300.0f, 225.0f, 200.0f, 150.0f}; // x, y, width, height
        SDL_RenderFillRect(renderer, &rect);

        // Draw Lines
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderLine(renderer, 0, 0, 800, 600);
        SDL_RenderLine(renderer, 0, 600, 800, 0);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
        for (int i = 0; i < 500; i++) {
            SDL_RenderPoint(renderer, SDL_randf() * 200.0f + 300.0f, SDL_randf() * 150.0f+ 225.0f);
        }
        // Present the rendered frame
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
