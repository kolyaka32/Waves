/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "cube.hpp"


void Cube::reset() {
    x = 0.0f;
    vx = 0.0f;
    mass = 1.0;
    type = Normal;
    temp = 0.0f;
}

void Cube::setType(Click _type) {
    switch (_type) {
    case Click::Normal:
        type = Normal;
        mass = 1.0;
        break;

    case Click::Heavy:
        type = Heavy;
        mass = 2.0;
        break;

    case Click::Wall:
        type = Wall;
        mass = 9000.0;
        break;

    case Click::Source:
        type = Source;
        mass = 1.0;
        break;
    
    default:
        break;
    }
}
