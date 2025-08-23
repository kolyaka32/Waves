/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "cube.hpp"


class CubeTexture {
private:
    const Window& window;
    SDL_Texture* texture;

public:
    CubeTexture(const Window& window);
    ~CubeTexture();
    void blit(float x, float y) const;
};
