/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "musicNames.hpp"

// Check, if use mixer and preload music
#if USE_SDL_MIXER && PRELOAD_MUSIC

// File names of the corresponding music
const char* musicFilesNames[unsigned(Music::Count)] = {

};

#endif  // USE_SDL_MIXER && PRELOAD_MUSIC
