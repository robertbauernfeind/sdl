//
// Created by r.bauernfeind on 02.04.2025.
//

#include "Head.h"

#include "GlobalState.h"

void Head::draw() const {
    SDL_SetRenderDrawColor(gState.renderer, color.r, color.g, color.b, color.a);

    float offset = (float)gState.baseStep - (float)gState.headSize;
    if (offset < 0) {
        offset = 0;
    }

    const SDL_FRect head = {
        (float) x + (offset / 2.0f),
        (float) y - (offset / 2.0f),
        (float)gState.headSize,
        (float)gState.headSize};
    SDL_RenderFillRect(gState.renderer, &head);

    for (const auto tail: tails) {
        tail.draw();
    }
}

void Head::changeDirection(const Direction dir) {
    direction = dir;
}

void Head::move() {
    const int step = gState.baseStep;
    int newX = x;
    int newY = y;
    switch (direction) {
        case Direction::UP:
            newY = y - step;

            if (newY < 0) {
                newY = gState.height - step;
            }
            break;
        case Direction::DOWN:
            newY = y + step;

            if (newY > gState.height - step) {
                newY = 0;
            }
            break;
        case Direction::LEFT:
            newX = x - step;

            if (newX < 0) {
                newX = gState.width - step;
            }
            break;
        case Direction::RIGHT:
            newX = x + step;

            if (newX > gState.width - step) {
                newX = 0;
            }
            break;
        default:
            break;
    }

    for (size_t i = 0; i < tails.size(); i++) {
        const size_t revIdx = tails.size() - 1 - i;
        if (revIdx == 0) {
            tails[revIdx].move(x, y);
            tails[revIdx].setDirection(direction);
        } else {
            const Tail lastTail = tails[revIdx - 1];
            tails[revIdx].move(lastTail.getX(), lastTail.getY());
            tails[revIdx].setDirection(lastTail.getDirection());
        }
    }

    y = newY;
    x = newX;
}

void Head::addTail() {
    const int step = gState.baseStep;
    Tail newTail;
    if (tails.empty()) {
        switch (direction) {
            case Direction::UP:
                newTail = Tail(x, y + step);
                break;
            case Direction::DOWN:
                newTail = Tail(x, y - step);
                break;
            case Direction::LEFT:
                newTail = Tail(x + step, y);
                break;
            case Direction::RIGHT:
                newTail = Tail(x - step, y);
                break;
            default:
                break;
        }
    } else {
        const Tail lastTail = tails.back();
        int newX = 0, newY = 0;

        switch (lastTail.getDirection()) {
            case Direction::UP:
                newX = lastTail.getX();
                newY = lastTail.getY() + step;
                break;
            case Direction::DOWN:
                newX = lastTail.getX();
                newY = lastTail.getY() - step;
                break;
            case Direction::LEFT:
                newX = lastTail.getX() + step;
                newY = lastTail.getY();
                break;
            case Direction::RIGHT:
                newX = lastTail.getX() - step;
                newY = lastTail.getY();
                break;
            default:
                break;
        }

        newTail = Tail{newX, newY};
    }

    tails.push_back(newTail);
}
