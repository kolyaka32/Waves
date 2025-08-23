/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseCycle.hpp"


// Base cycle class
BaseCycle::BaseCycle(Window& _window)
: CycleTemplate(_window),
field(window, 50, 50) {}

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

void BaseCycle::inputMouseWheel(float _wheelY) {
    
}

void BaseCycle::draw() const {
    window.setDrawColor(BLUE);
    window.clear();
    field.blit();
    window.render();
}
