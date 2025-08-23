/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../data/app.hpp"


// Namespace of objects for GUI (Graphic User Interface)
namespace GUI {
    // Text aligment type
    enum class Aligment : unsigned {
        Left,
        Midle,
        Right,
    };


    // Object, that will be drawn at screen
    class Template {
     protected:
        const Window& window;

     public:
        Template(const Window& window);
        virtual void blit() const;
    };


    // Object with texture, that will be drawn
    class TextureTemplate : public Template {
     protected:
        SDL_Texture* texture;
        SDL_FRect rect;

     public:
        TextureTemplate(const Window& window);
        void blit() const override;
        virtual bool in(const Mouse mouse) const;
    };


    // Class of rounded backplate for better understability
    class RoundedBackplate : public TextureTemplate {
     public:
        RoundedBackplate(const Window& window, float centerX, float centerY, float width, float height,
            float radius, float border, Color frontColor = GREY, Color backColor = BLACK);
        RoundedBackplate(const Window& window, const SDL_FRect& rect, float radius, float border,
            Color frontColor = GREY, Color backColor = BLACK);
        ~RoundedBackplate();
    };


    // Class with rectangular backplate for typeBox
    class RectBackplate : public TextureTemplate {
     public:
        RectBackplate(const Window& window, float centerX, float centerY, float width, float height,
            float border, Color frontColor = GREY, Color backColor = BLACK);
        RectBackplate(const Window& window, const SDL_FRect& rect,
            float border, Color frontColor = GREY, Color backColor = BLACK);
        ~RectBackplate();
    };
}  // namespace GUI
