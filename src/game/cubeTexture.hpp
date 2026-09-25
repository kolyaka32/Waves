/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "cube.hpp"


class CubeTexture {
private:
    const Window& window;
    SDL_Texture* texture;

public:
    static const float side;

    CubeTexture(const Window& window, Color upper, Color left, Color right);
    ~CubeTexture();
    void blit(const SDL_FPoint p) const;
};
