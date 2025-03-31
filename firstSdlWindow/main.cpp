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
    uniform_real_distribution<float> distrSize{0, 100};

    // for (int i = 0; i < 10; i++) {
    //     const float size(distrSize(gen));
    //     MovingPoint point{
    //         Vec2D{SDL_randf() * static_cast<float>(gState.width), SDL_randf() * static_cast<float>(gState.height)},
    //         Vec2D{distrVel(gen), distrVel(gen)},
    //         SDL_Color{
    //             static_cast<Uint8>(distrColor(gen)),
    //             static_cast<Uint8>(distrColor(gen)),
    //             static_cast<Uint8>(distrColor(gen)),
    //             255
    //         },
    //         size,
    //         size
    //     };
    //     points.push_back(point);
    // }

    // // Red
    // points.emplace_back(
    //     Vec2D{200, 400},
    //     Vec2D{0.0, 0.0},
    //     SDL_Color{255, 0, 0, 255},
    //     100,
    //     100
    // );
    //
    // // Green
    points.emplace_back(
        Vec2D{550, 400},
        Vec2D{70.0f, 70.0f},
        SDL_Color{0, 255, 0, 255},
        50,
        50
    );
    //
    // // Blue
    // points.emplace_back(
    //     Vec2D{200, 100},
    //     Vec2D{0.0f, 8.0f},
    //     SDL_Color{0, 0, 255, 255},
    //     50,
    //     50
    // );

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
        // do logic here

        Uint64 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        SDL_SetRenderDrawColor(gState.renderer, 0, 0, 0, 255);
        SDL_RenderClear(gState.renderer);

        for (auto &point: points) {
            point.update(deltaTime, true);

            for (auto &p1: points) {
                if (point.getTranslatedX() == p1.getTranslatedX() && point.getTranslatedY() == p1.getTranslatedY()) {
                    continue;
                }

                point.handlePointCollision(p1);
                // if (point.isColliding(p1)) {
                //     SDL_Log("Colliding");
                // }
            }

            point.draw();
        }

        SDL_RenderPresent(gState.renderer);
    }

    SDL_DestroyWindow(gState.window);
    SDL_Quit();

    return 0;
}
