/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "data/app.hpp"


// Main function
int main(int argv, char **args) {
    // Creating main window
    Window window{1000, 800, {"Something", "Штука", "", ""}};

    // Running menu
    App::run(window);

    // Successful end of program
    return 0;
}
