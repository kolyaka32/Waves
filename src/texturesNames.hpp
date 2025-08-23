/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once


// Names of all images with related numbers
enum class Textures : unsigned {
    // Global counter of all textures
    Count,
};

// Operators for change textures depend on offset
Textures operator+(const Textures index, int offset);
Textures operator-(const Textures index, int offset);

// File names of the corresponding textures
extern const char* texturesFilesNames[unsigned(Textures::Count)];
