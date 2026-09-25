/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "field.hpp"


Field::Field(const Window& _window, int _width, int _height)
: window(_window),
width(_width),
height(_height),
normalTexture(_window, {88, 133, 186, 255}, {65, 90, 140, 255}, {160, 217, 247, 255}),
heavyTexture(_window, {0x1f, 0xab, 0x89, 255}, {0x62, 0xd2, 0xa2, 255}, {0x9d, 0xd3, 0xc3, 255}),
wallTexture(_window, {120, 120, 120, 255}, {90, 90, 90, 255}, {190, 190, 190, 255}) {
    field = new Cube[width*height];
    reset();
}

Field::~Field() {
    delete[] field;
}

void Field::reset() {
    for (int i = 0; i < width*height; ++i) {
        field[i].reset();
    }
    type = Click::Push;
    pushForce = 20.0;
    clicking = false;
}

bool Field::isValid(SDL_Point point) {
    return (point.x > 0 && point.x < width-1 &&
        point.y > 0 && point.y < height-1);
}

SDL_Point Field::getRelative(const Mouse _mouse) const {
    return {int((_mouse.getX() + 2*_mouse.getY()-500) / CubeTexture::side) + height/4,
        int((2*_mouse.getY() - _mouse.getX()+500) / CubeTexture::side) + height/4};
}

SDL_FPoint Field::getAbsolute(int x, int y, float h) const {
    return {CubeTexture::side*(float(x)/2 - float(y)/2 - 0.5f) + 500.0f,
        CubeTexture::side*(float(x)/4 + float(y)/4 - height/8) - h};
}

void Field::click() {
    Mouse mouse;
    mouse.updatePos();
    SDL_Point p = getRelative(mouse);
    if (isValid(p)) {
        switch (type) {
        case Click::Push:
            // Pushing
            field[p.x+p.y*width].x += pushForce;
            break;

        case Click::Normal:
        case Click::Heavy:
        case Click::Wall:
        case Click::Source:
            clicking = true;
            break;

        default:
            break;
        }
    }
}

void Field::unclick() {
    clicking = false;
}

void Field::press(SDL_Keycode _key) {
    switch (_key) {
    case SDLK_1:
        type = Click::Push;
        break;

    case SDLK_2:
        type = Click::Normal;
        break;

    case SDLK_3:
        type = Click::Heavy;
        break;

    case SDLK_4:
        type = Click::Wall;
        break;

    case SDLK_5:
        type = Click::Source;
        break;

    case SDLK_0:
        type = Click::None;
        break;

    case SDLK_R:
        reset();
        break;

    default:
        break;
    }
}

void Field::wheelScroll(float wheel) {
    if (wheel < 0) {
        for (;wheel < 0; ++wheel) {
            pushForce /= 1.2;
        }
        if (pushForce < 0.1) {
            pushForce = 0.1;
        }
    } else {
        for (;wheel > 0; --wheel) {
            pushForce *= 1.2;
        }
        if (pushForce > 500) {
            pushForce = 500;
        }
    }
}

float Field::getDelta(int x, int y) {
    return (field[(y-1)*width+x-1].x +
        field[(y-1)*width+x].x +
        field[(y-1)*width+x+1].x +
        field[y*width+x-1].x +
        field[y*width+x+1].x +
        field[(y+1)*width+x-1].x +
        field[(y+1)*width+x].x +
        field[(y+1)*width+x+1].x)/8 -
        field[y*width+x].x;
}

void Field::update() {
    // Interaction
    if (clicking) {
        Mouse mouse;
        mouse.updatePos();
        SDL_Point p = getRelative(mouse);
        field[p.x+p.y*width].setType(type);
    }

    // Physics
    for (int y = 1; y < height-1; ++y) {
        for (int x = 1; x < width-1; ++x) {
            // Update speed as spring
            field[y*width+x].vx += springKoef*getDelta(x, y);
            // Get new position
            field[y*width+x].temp = field[y*width+x].x + field[y*width+x].vx;
        }
    }
    // Set new position
    for (int i=0; i < width*height; ++i) {
        field[i].x = field[i].temp;
    }
    // Friction
    for (int i=0; i < width*height; ++i) {
        field[i].vx *= friction;
    }
}

void Field::blit() const {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            SDL_FPoint p = getAbsolute(x, y, field[y*width+x].x);
            switch (field[y*width+x].type) {
            case Normal:
                normalTexture.blit(p);
                break;

            case Heavy:
                heavyTexture.blit(p);
                break;

            case Wall:
                wallTexture.blit(p);
                break;

            case Source:
                heavyTexture.blit(p);
                break;

            default:
                break;
            }
            
        }
    }
    window.setDrawColor(WHITE);
    window.drawDebugText(10.0, 10.0, "Reset: \'r\'");
    switch (type) {
    case Click::None:
        window.drawDebugText(10.0, 25.0, "None");
        break;

    case Click::Push:
        window.drawDebugText(10.0, 25.0, "Push, force: %.1f", pushForce);
        break;

    case Click::Normal:
        window.drawDebugText(10.0, 25.0, "Place wall");
        break;

    case Click::Heavy:
        window.drawDebugText(10.0, 25.0, "Place heavy");
        break;

    case Click::Wall:
        window.drawDebugText(10.0, 25.0, "Place wall");
        break;

    case Click::Source:
        window.drawDebugText(10.0, 25.0, "Place source");
        break;

    default:
        break;
    }
}
