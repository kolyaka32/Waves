/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../data/app.hpp"


class Cube {
private:
    float height;
    float posX, posY;

public:
    void init(int X, int Y);
    void setH(float t, int x, int y);
    float getX();
    float getY();
    const static int side = 64;
};
