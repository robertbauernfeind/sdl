#include <iostream>
#include "SDL3/SDL.h"

using namespace std;

int main() {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Startup");

    return 0;
}