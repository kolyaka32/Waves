/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "data/libraries.hpp"
#include "cycles/baseCycle.hpp"


// Selecting loader for data, depend on testing
Libraries libraries;

// Main function
int main(int argv, char **args) {
    // Creating main window
    Window window{1000, 800, {"Something", "Штука"}};

    // Running menu
    CycleTemplate::runCycle<BaseCycle>(window);

    // Successful end of program
    return 0;
}
