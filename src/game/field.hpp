/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "cube.hpp"
#include "cubeTexture.hpp"


class Field {
private:
    // Field
    const int width, height;
    Cube* field;
    float* temp;
    // Physics constants
    const float springKoef = 0.8;
    const float friction = 0.99;

    // Interaction
    bool clicking = false;
    float pushForce = 20.0;

    // Graphic part
    const CubeTexture texture;
    const Window& window;

    // Return delta between point and neighbours
    float getDelta(int x, int y);

    //
    bool isValid(SDL_Point point);
    SDL_Point getRelative(const Mouse mouse) const;
    SDL_FPoint getAbsolute(int x, int y, float h) const;

public:
    Field(const Window& window, int width, int height);
    ~Field();
    void reset();

    // Interaction
    void click();
    void wheelScroll(float wheel);
    void update();
    void blit() const;
};
