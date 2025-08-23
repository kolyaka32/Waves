/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once


class Cube {
private:
    float height;

public:
    void init();
    void setH(float t, int x, int y);
    float getX(int x);
    float getY(int y);
};
