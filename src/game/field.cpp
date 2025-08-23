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
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            field[y*width+x].init(x, y);
        }
    }
    t = 0.0;
}

Field::~Field() {
    delete[] field;
}

void Field::click(const Mouse mouse) {
    
}

void Field::update() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            field[y*width+x].setH(t, x, y);
        }
    }
    t += 0.1;
}

void Field::blit() const {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            texture.blit(field[y*width+x].getX(), field[y*width+x].getY());
        }
    }
}
