/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "define.hpp"


// Check, if use fonts and preload it
#if (USE_SDL_FONT) && (PRELOAD_FONTS)


// Names of fonts
enum class Fonts {
    Main,  // Main using font (now only one)

    // Global counter of all loaded fonts
    Count,
};

// File names of the corresponding fonts
extern const char* fontsFilesNames[unsigned(Fonts::Count)];

#endif  // (USE_SDL_FONT) && (PRELOAD_FONTS)
