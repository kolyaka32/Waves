/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "cube.hpp"
#include <SDL3/SDL.h>

void Cube::init() {
    height = 0;
}

void Cube::setH(float t, int x, int y) {
    height = SDL_sinf(t + x * 0.1f + y * 0.1f);
}

float Cube::getX(int x) {
    return x*64;
}

float Cube::getY(int y) {
    return y*64 + height;
}
