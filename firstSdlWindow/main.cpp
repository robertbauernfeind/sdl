#include <iostream>
#include <random>
#include <vector>

#include "classes/MovingPoint.h"
#include "classes/Vec2D.h"
#include "SDL3/SDL.h"
#include "classes/GlobalState.h"

using namespace std;

int main() {
    gState.width = 800;
    gState.height = 600;

    SDL_Log("%s", "Hello World from my first SDL3 project!");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_Init: %s\n", SDL_GetError());
        return 1;
    }

    bool done = false;

    if (!SDL_CreateWindowAndRenderer(
        "Hello World",
        gState.width,
        gState.height,
        SDL_WINDOW_OPENGL,
        &gState.window,
        &gState.renderer
    ))

        if (gState.window == nullptr) {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to create window: %s", SDL_GetError());
            return 1;
        }


    Uint64 lastTime = SDL_GetTicks();
    vector<MovingPoint> points;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> distrVel{-100, 100};
    uniform_real_distribution<float> distrColor{0, 255};

    for (int i = 0; i < 200; i++) {
        MovingPoint point{
            Vec2D{SDL_randf() * static_cast<float>(gState.width), SDL_randf() * static_cast<float>(gState.height)},
            Vec2D{distrVel(gen), distrVel(gen)},
            SDL_Color{
                static_cast<Uint8>(distrColor(gen)),
                static_cast<Uint8>(distrColor(gen)),
                static_cast<Uint8>(distrColor(gen)),
                255
            },
            10.0f
        };
        points.push_back(point);
    }

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Starting main loop");
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

        Uint64 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        SDL_SetRenderDrawColor(gState.renderer, 0, 0, 0, 255);
        SDL_RenderClear(gState.renderer);
        // do logic here
        // Clear screen with black
        //
        // // Draw red rectangle
        // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        // SDL_FRect rect = {300.0f, 225.0f, 200.0f, 150.0f}; // x, y, width, height
        // SDL_RenderFillRect(renderer, &rect);

        // Draw Lines
        // SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
        // SDL_RenderLine(renderer, 0, 0, 800, 600);
        // SDL_RenderLine(renderer, 0, 600, 800, 0);
        // SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
        // for (int i = 0; i < 500; i++) {
        //     SDL_RenderPoint(renderer, SDL_randf() * 200.0f + 300.0f, SDL_randf() * 150.0f+ 225.0f);
        // }

        for (auto &point: points) {
            point.update(deltaTime);
            point.draw();
        }
        SDL_RenderPresent(gState.renderer);
    }

    SDL_DestroyWindow(gState.window);
    SDL_Quit();

    return 0;
}
