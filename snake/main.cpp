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
    constexpr int offsetX = 0;
    const int offsetY = 0;
    for (int i = (offsetY / 2); i <= height - (offsetY / 2); i += 50) {
        SDL_RenderLine(
            renderer,
            static_cast<float>(i),
            (offsetY / 2.0f),
            static_cast<float>(i),
            static_cast<float>(height) - (offsetY / 2.0f)
        );
    }

    for (int i = (offsetX / 2); i <= width - (offsetX / 2); i += 50) {
        SDL_RenderLine(
            renderer,
            (offsetX / 2.0f),
            static_cast<float>(i),
            static_cast<float>(width) - (offsetX / 2.0f),
            static_cast<float>(i)
        );
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
    float accumulator = 0.0f;
    const float fixedTimeStep = 0.5f; // 100ms Update-Intervall

    auto snake = Head();

    while (!done) {
        SDL_Event event;
        const auto currentTime = SDL_GetTicks();
        const auto deltaTime = (currentTime - lastTime) / 1000;
        lastTime = currentTime;
        accumulator += deltaTime;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    done = true;
                    break;
                case SDL_EVENT_KEY_DOWN:
                    switch (event.key.key) {
                        case SDLK_UP:
                            snake.changeDirection(Direction::UP);
                            break;
                        case SDLK_DOWN:
                            snake.changeDirection(Direction::DOWN);
                            break;
                        case SDLK_LEFT:
                            snake.changeDirection(Direction::LEFT);
                            break;
                        case SDLK_RIGHT:
                            snake.changeDirection(Direction::RIGHT);
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


        // do logic here
        drawGrid();

        // move
        while (accumulator >= fixedTimeStep) {
            snake.move();
            accumulator -= fixedTimeStep;
        }

        snake.draw(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
