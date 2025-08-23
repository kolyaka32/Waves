/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "cubeTexture.hpp"


CubeTexture::CubeTexture(const Window& _window)
: window(_window) {
    // Create texture
    texture = window.createTexture(Cube::side, Cube::side);
    window.setRenderTarget(texture);

    // Upper part
    window.setDrawColor({88, 133, 186, 255});
    for (int i=0; i < Cube::side/4; ++i) {
        window.drawLine(Cube::side/2-i*2, i, Cube::side/2+i*2, i);
    }
    for (int i=0; i < Cube::side/4; ++i) {
        window.drawLine(2*i, i+Cube::side/4, Cube::side-i*2, i+Cube::side/4);
    }

    // Left part
    window.setDrawColor({65, 90, 140, 255});
    for (int i=0; i < Cube::side/2; ++i) {
        window.drawLine(0, i+Cube::side/4, Cube::side/2, i+Cube::side/2);
    }

    // Right part
    window.setDrawColor({160, 217, 247, 255});
    for (int i=0; i < Cube::side/2; ++i) {
        window.drawLine(Cube::side, i+Cube::side/4, Cube::side/2, i+Cube::side/2);
    }

    // Internal frame
    window.setDrawColor(WHITE);
    window.drawLine(0,             Cube::side/4, Cube::side/2, Cube::side/2);
    window.drawLine(Cube::side,    Cube::side/4, Cube::side/2, Cube::side/2);
    window.drawLine(Cube::side/2,  Cube::side/2, Cube::side/2, Cube::side);

    // External frame
    window.setDrawColor(BLACK);
    window.drawLine(0,            Cube::side/4,     Cube::side/2, 0);
    window.drawLine(Cube::side,   Cube::side/4,     Cube::side/2, 0);
    window.drawLine(0,            Cube::side/4,     0,            Cube::side*3/4-1);
    window.drawLine(Cube::side-1, Cube::side/4,     Cube::side-1, Cube::side*3/4-1);
    window.drawLine(0,            Cube::side*3/4-1, Cube::side/2, Cube::side-1);
    window.drawLine(Cube::side-1, Cube::side*3/4-1, Cube::side/2, Cube::side-1);

    // End
    window.resetRenderTarget();
}

CubeTexture::~CubeTexture() {
    SDL_DestroyTexture(texture);
}

void CubeTexture::blit(float x, float y) const {
    SDL_FRect rect = {x, y, float(texture->w), float(texture->h)};
    window.blit(texture, rect);
}
