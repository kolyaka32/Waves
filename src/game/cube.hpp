/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../data/app.hpp"


// Posiible type of cell
enum Type {
    Normal,
    Heavy,
    Wall,
    Source,
};

// Possible types of interaction
enum class Click {
    None,
    // Straight interact
    Push,
    // Placement
    Normal,
    Heavy,
    Wall,
    Source,
};

// Single object parameters
class Cube {
public:
    float x = 0;
    float vx = 0;
    float inertion = 1.0;  // 1/mass
    int type = Normal;

    void reset();
    void setType(Click type);
};
