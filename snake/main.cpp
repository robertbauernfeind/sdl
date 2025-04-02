#include <iostream>

#include "Head.h"
#include "SDL3/SDL.h"

using namespace std;

int height = 800;
int width = 800;

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

void drawGrid() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int offsetX = 50;
    int offsetY = 50;
    for (int i = (offsetY / 2); i <= height - (offsetY / 2); i += 50) {
        SDL_RenderLine(renderer, i, (offsetY / 2), i, height - (offsetY / 2));
    }

    for (int i = (offsetX / 2); i <= width - (offsetX / 2); i += 50) {
        SDL_RenderLine(renderer, (offsetX / 2), i, width - (offsetX / 2), i);
    }
}

int main() {
    SDL_Log("%s", "Snake startup");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_Init: %s\n", SDL_GetError());
        return 1;
    }

    bool done = false;

    if (!SDL_CreateWindowAndRenderer(
        "Snake",
        width,
        height,
        SDL_WINDOW_OPENGL,
        &window,
        &renderer
    ))

        if (window == nullptr) {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to create window: %s", SDL_GetError());
            return 1;
        }


    Uint64 lastTime = SDL_GetTicks();
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Starting main loop");

    Head snake = Head();

    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    done = true;
                    break;
                case SDL_EVENT_KEY_DOWN:
                    switch (event.key.key) {
                        case SDLK_UP:
                            snake.move(0);
                            break;
                        case SDLK_DOWN:
                            snake.move(1);
                            break;
                        case SDLK_LEFT:
                            snake.move(2);
                            break;
                        case SDLK_RIGHT:
                            snake.move(3);
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        drawGrid();

        // do logic here

        Uint64 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;
        SDL_Delay(250);
        snake.draw(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
