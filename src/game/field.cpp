/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "field.hpp"


Field::Field(const Window& _window, int _width, int _height)
: window(_window),
width(_width),
height(_height),
texture(_window) {
    field = new Cube[width*height];
    temp = new float[width*height];
    reset();
}

Field::~Field() {
    delete[] field;
    delete[] temp;
}

void Field::reset() {
    for (int i = 0; i < width*height; ++i) {
        field[i].x = 0.0f;
        field[i].vx = 0.0f;
        temp[i] = 0.0f;
    }
}

bool Field::isValid(SDL_Point point) {
    return (point.x > 0 && point.y > 0 && point.x < width-1 && point.y < height-1);
}

SDL_Point Field::getRelative(const Mouse _mouse) const {
    return {int((_mouse.getX() + 2*_mouse.getY()-500) / CubeTexture::side) + height/4,
        int((2*_mouse.getY() - _mouse.getX()+500) / CubeTexture::side) + height/4};
}

SDL_FPoint Field::getAbsolute(int x, int y, float h) const {
    return {CubeTexture::side*(float(x)/2 - float(y)/2 - 0.5f) + 500.0f,
        CubeTexture::side*(float(x)/4 + float(y)/4 - height/8) - h};
}

void Field::click() {
    Mouse mouse;
    mouse.updatePos();
    SDL_Point p = getRelative(mouse);
    if (isValid(p)) {
        field[p.x+p.y*width].x += pushForce;
    }
}

void Field::wheelScroll(float wheel) {
    if (wheel < 0) {
        for (;wheel < 0; ++wheel) {
            pushForce /= 1.2;
        }
        if (pushForce < 0.1) {
            pushForce = 0.1;
        }
    } else {
        for (;wheel > 0; --wheel) {
            pushForce *= 1.2;
        }
        if (pushForce > 500) {
            pushForce = 500;
        }
    }
}

float Field::getDelta(int x, int y) {
    return (field[(y-1)*width+x-1].x +
        field[(y-1)*width+x].x +
        field[(y-1)*width+x+1].x +
        field[y*width+x-1].x +
        field[y*width+x+1].x +
        field[(y+1)*width+x-1].x +
        field[(y+1)*width+x].x +
        field[(y+1)*width+x+1].x)/8 -
        field[y*width+x].x;
}

void Field::update() {
    for (int y = 1; y < height-1; ++y) {
        for (int x = 1; x < width-1; ++x) {
            // Update speed as spring
            field[y*width+x].vx += springKoef*getDelta(x, y);
            // Get new position
            temp[y*width+x] = field[y*width+x].x + field[y*width+x].vx;
        }
    }
    // Set new position
    for (int i=0; i < width*height; ++i) {
        field[i].x = temp[i];
    }
    // Friction
    for (int i=0; i < width*height; ++i) {
        field[i].vx *= friction;
    }
}

void Field::blit() const {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            texture.blit(getAbsolute(x, y, field[y*width+x].x));
        }
    }
    window.setDrawColor(WHITE);
    window.drawDebugText(10.0, 10.0, "Force: %f", pushForce);
    window.drawDebugText(10.0, 25.0, "Reset: \'r\'");
}
