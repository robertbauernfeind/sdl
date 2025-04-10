//
// Created by r.bauernfeind on 02.04.2025.
//

#include "Head.h"

#include "GlobalState.h"

void Head::draw() const {
    SDL_SetRenderDrawColor(gState.renderer, color.r, color.g, color.b, color.a);

    const SDL_FRect head = {(float) x, (float) y, 50, 50};
    SDL_RenderFillRect(gState.renderer, &head);

    for (const auto tail: tails) {
        tail.draw();
    }
}

void Head::changeDirection(const Direction dir) {
    direction = dir;
}

void Head::move() {
    const int step = 50;
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

    for (size_t i = 0; i < tails.size(); ++i) {
        if (i == 0) {
            tails[i].move(x, y);
            tails[i].setDirection(direction);
        } else {
            const Tail lastTail = tails[i - 1];
            tails[i].move(lastTail.getX(), lastTail.getY());
            tails[i].setDirection(lastTail.getDirection());
        }
    }

    y = newY;
    x = newX;
}

void Head::addTail() {
    const int step = 50;
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
