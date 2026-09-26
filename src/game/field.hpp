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
    float time;
    const float springKoef = 1.0;
    const float frictions[8] = {0.1, 0.5, 0.8, 0.9, 0.95, 0.99, 0.999, 1.0};
    const float minForce = 0.1;
    const float maxForce = 1000.0;

    // Interaction
    SDL_MouseButtonFlags clicking;
    Click type;  // Type of interaction
    float pushForce;
    int frictionVar;
    const float sourceAmp = 40.0;
    float sourceFreq = 0.2;

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
    void scroll(float& val, float wheelY) const;

    void interact(Cube& cube1, Cube& cube2) const;

public:
    Field(const Window& window, int width, int height);
    ~Field();
    void reset();

    // Interaction
    bool click(const Mouse mouse);
    void unclick();
    bool press(SDL_Keycode key);
    bool wheelScroll(float wheelY);
    void update(const Mouse mouse);
    void blit() const;
};
