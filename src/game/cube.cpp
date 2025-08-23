/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "cube.hpp"
#include <SDL3/SDL.h>

void Cube::init(int x, int y) {
    /*if (y % 2 == 0) {
        posX = x*side/2;
    } else {
        posX = x*side/2 + side/4;
    }
    posY = y*side + x*side/2;
    height = 0;*/
    posX = 0;
    posY = 0;
}

void Cube::setH(float t, int x, int y) {
    //height = SDL_sinf(posX + posY) * 1.0f;
}

float Cube::getX() {
    return posX;
}

float Cube::getY() {
    return posY + height;
}
