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
    Cube* field1;
    Cube* field2;
    float t = 0.0;
    bool clicking = false;

public:
    Field(const Window& window, int width, int height);
    ~Field();
    SDL_Point getRelativePos();
    bool isValid(SDL_Point point);
    void click();
    void unclick();
    void swap();
    void update();
    void blit() const;
};
