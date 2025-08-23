/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "texturesNames.hpp"


// File names of the corresponding textures
const char* texturesFilesNames[unsigned(Textures::Count)] = {

};

Textures operator+(const Textures _color, int _offset) {
    return Textures(unsigned(_color) + _offset);
}

Textures operator-(const Textures _color, int _offset) {
    return Textures(unsigned(_color) - _offset);
}
