/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../data/app.hpp"


// Possible types of cube
enum Type {
    None,
    Wall,
    Source,
};

// Single object parameters
class Cube {
public:
    float x = 0;
    float vx = 0;
    int type = None;
};
