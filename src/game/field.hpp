/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "cubeTexture.hpp"


class Field {
private:
    // Field
    const int width, height;
    Cube* field;
    // Physics constants
    const float springKoef = 1.0;
    const float friction = 0.99;

    // Interaction
    bool clicking = false;
    Click type;  // Type of interaction
    float pushForce;

    // Graphic part
    const CubeTexture normalTexture;
    const CubeTexture lightTexture;
    const CubeTexture heavyTexture;
    const CubeTexture wallTexture;
    const Window& window;

    //
    bool isValid(SDL_Point point);
    SDL_Point getRelative(const Mouse mouse) const;
    SDL_FPoint getAbsolute(int x, int y, float h) const;

    void interact(Cube& cube1, Cube& cube2) const;

public:
    Field(const Window& window, int width, int height);
    ~Field();
    void reset();

    // Interaction
    void click();
    void unclick();
    void press(SDL_Keycode key);
    void wheelScroll(float wheel);
    void update();
    void blit() const;
};
