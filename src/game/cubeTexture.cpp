/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "cubeTexture.hpp"


CubeTexture::CubeTexture(const Window& _window)
: window(_window) {
    // Create texture
    const int sideLength = 16;
    texture = window.createTexture(sideLength*2, sideLength*2);
    window.setRenderTarget(texture);

    //window.setDrawColor(WHITE);
    //window.clear();

    // Upper part
    window.setDrawColor({88, 133, 186, 255});
    for (int i=0; i < sideLength/2; ++i) {
        window.drawLine(sideLength-i*2, i, sideLength+i*2, i);
    }
    for (int i=0; i < sideLength/2; ++i) {
        window.drawLine(2*i, i+sideLength/2, 2*sideLength-i*2, i+sideLength/2);
    }

    // Left part
    window.setDrawColor({65, 90, 140, 255});
    for (int i=0; i < sideLength; ++i) {
        window.drawLine(0, i+sideLength/2, sideLength, i+sideLength);
    }
    
    // Right part
    window.setDrawColor({100, 135, 150, 255});
    for (int i=0; i < sideLength; ++i) {
        window.drawLine(sideLength*2, i+sideLength/2, sideLength, i+sideLength);
    }

    // Internal frame
    window.setDrawColor(WHITE);
    window.drawLine(0, sideLength/2, sideLength, sideLength);
    window.drawLine(sideLength*2, sideLength/2, sideLength, sideLength);
    window.drawLine(sideLength, sideLength, sideLength, sideLength*2);

    // External frame
    window.setDrawColor(BLACK);
    window.drawLine(0,              sideLength/2,     sideLength,     0);
    window.drawLine(sideLength*2,   sideLength/2,     sideLength,     0);
    window.drawLine(0,              sideLength/2,     0,              sideLength*3/2-1);
    window.drawLine(sideLength*2-1, sideLength/2,     sideLength*2-1, sideLength*3/2-1);
    window.drawLine(0,              sideLength*3/2-1, sideLength,     sideLength*2-1);
    window.drawLine(sideLength*2-1, sideLength*3/2-1, sideLength,     sideLength*2-1);

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
