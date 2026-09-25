/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "cubeTexture.hpp"


const float CubeTexture::side = 32.0;

CubeTexture::CubeTexture(const Window& _window, Color _upper, Color _left, Color _right)
: window(_window) {
    // Create texture
    texture = window.createTexture(side, side);
    window.setRenderTarget(texture);

    // Upper part
    window.setDrawColor(_upper);
    for (int i=0; i < side/4; ++i) {
        window.drawLine(side/2-i*2, i, side/2+i*2, i);
    }
    for (int i=0; i < side/4; ++i) {
        window.drawLine(2*i, i+side/4, side-i*2, i+side/4);
    }

    // Left part
    window.setDrawColor(_left);
    for (int i=0; i < side/2; ++i) {
        window.drawLine(0, i+side/4, side/2, i+side/2);
    }

    // Right part
    window.setDrawColor(_right);
    for (int i=0; i < side/2; ++i) {
        window.drawLine(side, i+side/4, side/2, i+side/2);
    }

    // Internal frame
    window.setDrawColor(WHITE);
    window.drawLine(0,       side/4, side/2, side/2);
    window.drawLine(side,    side/4, side/2, side/2);
    window.drawLine(side/2,  side/2, side/2, side);

    // External frame
    window.setDrawColor(BLACK);
    window.drawLine(0,      side/4,     side/2, 0);
    window.drawLine(side,   side/4,     side/2, 0);
    window.drawLine(0,      side/4,     0,      side*3/4-1);
    window.drawLine(side-1, side/4,     side-1, side*3/4-1);
    window.drawLine(0,      side*3/4-1, side/2, side-1);
    window.drawLine(side-1, side*3/4-1, side/2, side-1);

    // End
    window.resetRenderTarget();
}

CubeTexture::~CubeTexture() {
    SDL_DestroyTexture(texture);
}

void CubeTexture::blit(const SDL_FPoint p) const {
    SDL_FRect rect = {p.x, p.y, float(texture->w), float(texture->h)};
    window.blit(texture, rect);
}
