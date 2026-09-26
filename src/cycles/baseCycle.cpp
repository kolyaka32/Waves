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
    field.unclick();
}

bool BaseCycle::inputMouseWheel(float _wheelY) {
    return field.wheelScroll(_wheelY);
}

bool BaseCycle::inputKeys(SDL_Keycode _key) {
    return field.press(_key);
}

void BaseCycle::draw() const {
    window.setDrawColor(BLUE);
    window.clear();
    field.blit();
    window.render();
}
