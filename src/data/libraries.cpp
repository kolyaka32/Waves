/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include <SDL3/SDL.h>
#include "libraries.hpp"


Libraries::Libraries() {
    // Load depend on teting
    #if CHECK_CORRECTION
    // Initialasing main library
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        throw LibararyLoadException("Main library: " + std::string(SDL_GetError()));
    }
    logAdditional("Libraries load correctly");
    #else
    SDL_Init(SDL_INIT_VIDEO);
    #endif
}

Libraries::~Libraries() noexcept {
    // Closing all library reversed
    SDL_Quit();
}
