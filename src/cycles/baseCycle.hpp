/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once


#include "../data/cycleTemplate.hpp"
#include "../GUI/interface.hpp"
#include "../game/field.hpp"


// Base cycle for use in any game mode
class BaseCycle : public CycleTemplate {
 protected:
    Field field;

 public:
    BaseCycle(Window& _window);
    bool inputMouseDown() override;
    void update() override;
    void inputMouseUp() override;
    void inputMouseWheel(float _wheelY) override;
    void inputKeys(SDL_Keycode key) override;
    void draw() const override;
};
