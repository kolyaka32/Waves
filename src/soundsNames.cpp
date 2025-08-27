/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "soundsNames.hpp"


// Check, if use mixer and preload sounds
#if (USE_SDL_MIXER) && (PRELOAD_SOUNDS)


// File names of the corresponding sounds
const char* soundsFilesNames[unsigned(Sounds::Count)] = {

};

#endif  // (USE_SDL_MIXER) && (PRELOAD_SOUNDS)
