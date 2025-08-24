/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "field.hpp"


Field::Field(const Window& _window, int _width, int _height)
: width(_width),
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

SDL_Point Field::getRelativePos() {
    Mouse mouse;
    mouse.updatePos();

    SDL_Point p;
    p.x = (mouse.getX() + 2*mouse.getY()-500) / Cube::side + height/4;
    p.y = (2*mouse.getY() - mouse.getX()+500) / Cube::side + height/4;
    return p;
}

bool Field::isValid(SDL_Point point) {
    return (point.x > 0 && point.y > 0 && point.x < width-1 && point.y < height-1);
}

void Field::click() {
    SDL_Point p = getRelativePos();
    if (isValid(p)) {
        field[p.x+p.y*width].x = size;
    }
}

void Field::wheelScroll(float wheel) {
    if (wheel < 0) {
        for (;wheel < 0; ++wheel) {
            size /= 1.2;
        }
    } else {
        for (;wheel > 0; --wheel) {
            size *= 1.2;
        }
    }
}

void Field::update() {
    // Updating field base on previos
    for (int y = 1; y < height-1; ++y) {
        for (int x = 1; x < width-1; ++x) {
            // Getting avarage of 4 neighbours
            field[y*width+x].vx +=
                0.8f*((field[(y-1)*width+x-1].x +
                field[(y-1)*width+x].x +
                field[(y-1)*width+x+1].x +
                field[y*width+x-1].x + 
                field[y*width+x+1].x +
                field[(y+1)*width+x-1].x +
                field[(y+1)*width+x].x +
                field[(y+1)*width+x+1].x)/8 -
                field[y*width+x].x);
            temp[y*width+x] = field[y*width+x].x + field[y*width+x].vx;
        }
    }
    for (int i=0; i < width*height; ++i) {
        field[i].x = temp[i];
    }

    /*
    // Smoothing function
    for (int i=0; i < width*height; ++i) {
        field1[i].height *= 0.8f;
    }*/
}

void Field::blit() const {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float X = Cube::side*(float(x)/2-float(y)/2 - 0.5) + 500;
            float Y = Cube::side*(float(x)/4+float(y)/4 - height/8) - field[y*width+x].x;
            texture.blit(X, Y);
        }
    }
}
