/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "field.hpp"


Field::Field(const Window& _window, int _width, int _height)
: width(_width),
height(_height),
texture(_window) {
    field1 = new Cube[width*height];
    field2 = new Cube[width*height];
    for (int i = 0; i < width*height; ++i) {
        field1[i].height = 0;
    }
}

Field::~Field() {
    delete[] field1;
    delete[] field2;
}

SDL_Point Field::getRelativePos() {
    Mouse mouse;
    mouse.updatePos();

    SDL_Point p;
    p.x = (mouse.getX() + 2*mouse.getY()-500) / Cube::side;
    p.y = (2*mouse.getY() - mouse.getX()+500) / Cube::side;
    return p;
}

bool Field::isValid(SDL_Point point) {
    return (point.x > 0 && point.y > 0 && point.x < width-1 && point.y < height-1);
}

void Field::click() {
    clicking = true;
}

void Field::unclick() {
    clicking = false;
}

void Field::swap() {
    Cube* temp = field2;
    field2 = field1;
    field1 = temp;
}

void Field::update() {
    // Clicking
    if (clicking) {
        SDL_Point p = getRelativePos();
        if (isValid(p)) {
            field1[p.x+p.y*width].height = 10;
        }
    }

    // Updating field base on previos
    for (int y = 1; y < height-1; ++y) {
        for (int x = 1; x < width-1; ++x) {
            // Getting avarage of 4 neighbours
            field2[y*width+x].height = 
                (field1[y*width+x-width-1].height +
                field1[y*width+x-width].height +
                field1[y*width+x-width+1].height +
                field1[y*width+x-1].height +
                field1[y*width+x].height +
                field1[y*width+x+1].height +
                field1[y*width+x+width-1].height +
                field1[y*width+x+width].height +
                field1[y*width+x+width+1].height)/9;
        }
    }
    swap();

    /*
    // Smoothing function
    for (int i=0; i < width*height; ++i) {
        field1[i].height *= 0.8f;
    }*/
}

void Field::blit() const {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            //float X = Cube::side*((float(x)/2-float(y)/2) + width/4);
            //float Y = Cube::side*((float(x)/4+float(y)/4) - height/16) - field1[y*width+x].height*10;
            float X = Cube::side*(float(x)/2-float(y)/2 - 0.5) + 500;
            float Y = Cube::side*(float(x)/4+float(y)/4) - field1[y*width+x].height*10;
            texture.blit(X, Y);
        }
    }
}
