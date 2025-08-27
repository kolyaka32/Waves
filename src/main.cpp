/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "data/preloaded/loader/loader.hpp"
#include "data/libraries.hpp"      // Global initialised libraries
#include "cycles/baseCycle.hpp"  // Start game cycle


// Initialasing global objects in correct order
Libraries libraries{};

#if (PRELOAD_DATA)
const DataLoader dataLoader{};
#endif

#if USE_SDL_MIXER && PRELOAD_MUSIC
SoundsData sounds{};
#endif

#if USE_SDL_MIXER && PRELOAD_SOUNDS
MusicData music{};
#endif

// Main function
int main(int argv, char **args) {
    // Creating main window
    Window window{1000, 800, {"Something", "Штука", "", ""}};

    // Running menu
    CycleTemplate::runCycle<BaseCycle>(window);

    // Successful end of program
    return 0;
}
