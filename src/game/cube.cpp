/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "cube.hpp"


void Cube::reset() {
    x = 0.0f;
    vx = 0.0f;
    inertion = 1.0;
    type = Normal;
}

void Cube::setType(Click _type) {
    switch (_type) {
    case Click::Normal:
        type = Normal;
        inertion = 1.0;
        break;

    case Click::Light:
        type = Light;
        inertion = 2.0;
        break;

    case Click::Heavy:
        type = Heavy;
        inertion = 0.1;
        break;

    case Click::Wall:
        type = Wall;
        inertion = 0.0;
        vx = 0.0;
        x = 0.0;
        break;

    case Click::Source:
        type = Source;
        inertion = 0.0;
        break;
    
    default:
        break;
    }
}
