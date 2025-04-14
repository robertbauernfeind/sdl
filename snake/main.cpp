#include <iostream>
#include <random>

#include "Head.h"
#include "SDL3/SDL.h"
#include "GlobalState.h"

using namespace std;

void drawGrid() {
    SDL_SetRenderDrawColor(gState.renderer, 255, 255, 255, 255);
    constexpr int offsetX = 0;
    const int offsetY = 0;
    for (int i = (offsetY / 2); i <= gState.height - (offsetY / 2); i += 50) {
        SDL_RenderLine(
            gState.renderer,
            static_cast<float>(i),
            (offsetY / 2.0f),
            static_cast<float>(i),
            static_cast<float>(gState.height) - (offsetY / 2.0f)
        );
    }

    for (int i = (offsetX / 2); i <= gState.width - (offsetX / 2); i += 50) {
        SDL_RenderLine(
            gState.renderer,
            (offsetX / 2.0f),
            static_cast<float>(i),
            static_cast<float>(gState.width) - (offsetX / 2.0f),
            static_cast<float>(i)
        );
    }
}

void spawnApple() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution distr{0, (gState.width / gState.baseStep) - 1};
    const int x = distr(gen) * 50;
    const int y = distr(gen) * 50;


    for (const auto &existingApple: gState.apples) {
        if (existingApple.getX() == x && existingApple.getY() == y) {
            return; // Apple already exists at this position
        }
    }

    for (const auto &tail : gState.snake.getTails()) {
        if (tail.getX() == x && tail.getY() == y) {
            return; // Apple is on the snake
        }
    }

    const Apple apple(x, y);
    gState.apples.push_back(apple);
}

void initGame() {
    for (int i = 0; i < 2; i++) {
        spawnApple();
    }

    gState.snake = Head{};
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
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Starting main loop");
    float accumulator = 0.0f;
    const float fixedTimeStep = 0.25f; // 100ms Update-Intervall

    initGame();

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
                            gState.snake.changeDirection(Direction::UP);
                            break;
                        case SDLK_DOWN:
                            gState.snake.changeDirection(Direction::DOWN);
                            break;
                        case SDLK_LEFT:
                            gState.snake.changeDirection(Direction::LEFT);
                            break;
                        case SDLK_RIGHT:
                            gState.snake.changeDirection(Direction::RIGHT);
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                    switch (event.button.button) {
                        case SDL_BUTTON_LEFT:
                            spawnApple();
                            break;
                        case SDL_BUTTON_RIGHT:
                            gState.snake.addTail();
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
        SDL_SetRenderDrawColor(gState.renderer, 0, 0, 0, 255);
        SDL_RenderClear(gState.renderer);

        Uint64 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;
        accumulator += deltaTime;

        // do logic here
        // drawGrid();

        // move
        while (accumulator >= fixedTimeStep) {
            gState.snake.move();
            accumulator -= fixedTimeStep;
        }

        for (const auto &apple: gState.apples) {
            apple.draw();
        }

        if (gState.snake.collidesWithApple()) {
            spawnApple();
        }

        if (gState.snake.collidesWithTail()) {
            SDL_Log("Game Over");
            done = true;
        }

        gState.snake.draw();

        SDL_RenderPresent(gState.renderer);
    }

    SDL_DestroyWindow(gState.window);
    SDL_Quit();

    return 0;
}
