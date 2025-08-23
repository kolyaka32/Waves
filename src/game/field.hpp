/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "cube.hpp"
#include "cubeTexture.hpp"


class Field {
private:
    const int width, height;
    const CubeTexture texture;
    Cube* field;
    float t;

public:
    Field(const Window& window, int width, int height);
    ~Field();
    void click(const Mouse mouse);
    void update();
    void blit() const;
};
