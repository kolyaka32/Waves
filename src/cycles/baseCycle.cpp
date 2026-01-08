/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseCycle.hpp"


// Base cycle class
BaseCycle::BaseCycle(Window& _window)
: CycleTemplate(_window),
field(window, 100, 100) {}

bool BaseCycle::inputMouseDown() {
    /*if (settings.click(mouse)) {
        return true;
    }*/
    field.click();
    return false;
}

void BaseCycle::update() {
    field.update();
}

void BaseCycle::inputMouseUp() {
    
}

void BaseCycle::inputMouseWheel(float _wheelY) {
    field.wheelScroll(_wheelY);
}

void BaseCycle::inputKeys(SDL_Keycode key) {
    switch (key) {
    case SDLK_R:
        field.reset();
        break;
    
    default:
        break;
    }
}

void BaseCycle::draw() const {
    window.setDrawColor(BLUE);
    window.clear();
    field.blit();
    window.render();
}
