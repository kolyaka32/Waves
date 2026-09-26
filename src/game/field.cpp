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
lightTexture(_window, {255, 255, 0, 255}, {255, 223, 0, 255}, {255, 237, 0, 255}),
heavyTexture(_window, {0x62, 0xd2, 0xa2, 255}, {0x1f, 0xab, 0x89, 255}, {0x9d, 0xd3, 0xc3, 255}),
wallTexture(_window, {90, 90, 90, 255}, {120, 120, 120, 255}, {190, 190, 190, 255}) {
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
    frictionVar = sizeof(frictions)/sizeof(*frictions)-1;
    pushForce = 20.0;
    clicking = 0;
    time = 0.0;
}

bool Field::isValid(SDL_Point point) {
    return (point.x > 0 && point.x < width-1 &&
        point.y > 0 && point.y < height-1);
}

SDL_Point Field::getRelative(const Mouse _mouse) const {
    return {int((_mouse.getX() + 2*_mouse.getY()-500-CubeTexture::side/2) / CubeTexture::side) + height/4,
        int((2*_mouse.getY() - _mouse.getX()+500-CubeTexture::side/2) / CubeTexture::side) + height/4};
}

SDL_FPoint Field::getAbsolute(int x, int y, float h) const {
    return {CubeTexture::side*(float(x)/2 - float(y)/2 - 0.5f) + 500.0f,
        CubeTexture::side*(float(x)/4 + float(y)/4 - height/8) - h};
}

bool Field::click(const Mouse _mouse) {
    SDL_Point p = getRelative(_mouse);
    if (isValid(p)) {
        switch (type) {
        case Click::Push:
            if (_mouse.getState() & SDL_BUTTON_LMASK) {
                field[p.x+p.y*width].x += pushForce;
            }
            if (_mouse.getState() & SDL_BUTTON_RMASK) {
                field[p.x+p.y*width].x -= pushForce;
            }
            break;

        case Click::Normal:
        case Click::Light:
        case Click::Heavy:
        case Click::Wall:
        case Click::Source:
            clicking = _mouse.getState();
            break;

        default:
            break;
        }
        return true;
    }
    return false;
}

void Field::unclick() {
    clicking = 0;
}

bool Field::press(SDL_Keycode _key) {
    switch (_key) {
    case SDLK_1:
        type = Click::Push;
        break;

    case SDLK_2:
        type = Click::Light;
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

    case SDLK_6:
        type = Click::Friction;
        break;

    case SDLK_0:
        type = Click::None;
        break;

    case SDLK_R:
        reset();
        break;

    default:
        return false;
    }
    return true;
}

void Field::scroll(float& _val, float _wheelY) const {
    if (_wheelY < 0) {
        for (;_wheelY < 0; ++_wheelY) {
            _val /= 1.2;
        }
        setMin(_val, minForce);
    } else {
        for (;_wheelY > 0; --_wheelY) {
            _val *= 1.2;
        }
        setMax(_val, maxForce);
    }
}

bool Field::wheelScroll(float _wheelY) {
    switch (type) {
    case Click::Push:
        scroll(pushForce, _wheelY);
        break;

    case Click::Source:
        scroll(sourceFreq, _wheelY);
        break;

    case Click::Friction:
        if (_wheelY < 0) {
            for (;_wheelY < 0; ++_wheelY) {
                frictionVar--;
            }
            setMin(frictionVar, 0);
        } else {
            for (;_wheelY > 0; --_wheelY) {
                frictionVar++;
            }
            setMax(frictionVar, 7);
        }
        break;

    default:
        break;
    }
    return true;
}

void Field::interact(Cube& _cube1, Cube& _cube2) const {
    float force = springKoef * (_cube1.x - _cube2.x) / 4;
    _cube1.vx -= force*_cube1.inertion;
    _cube2.vx += force*_cube2.inertion;
}

void Field::update(const Mouse _mouse) {
    // Interaction
    if (clicking) {
        SDL_Point p = getRelative(_mouse);
        if (isValid(p)) {
            if (clicking & SDL_BUTTON_LMASK) {
                field[p.x+p.y*width].setType(type);
            }
            if (clicking & SDL_BUTTON_RMASK) {
                field[p.x+p.y*width].setType(Click::Normal);
            }
        }
    }

    // Physics
    // Sources
    float sourcHeight = sourceAmp*SDL_sinf(time);
    time += sourceFreq;
    for (int i=0; i < width*height; ++i) {
        if (field[i].type == Source) {
            field[i].x = sourcHeight;
        }
    }

    // Vertical interactions
    for (int y = 0; y < height-1; ++y) {
        for (int x = 0; x < width; ++x) {
            interact(field[y*width+x], field[(y+1)*width+x]);
        }
    }
    // Horizontal interactions
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width-1; ++x) {
            interact(field[y*width+x], field[y*width+x+1]);
        }
    }
    for (int i=0; i < width*height; ++i) {
        // Friction
        field[i].vx *= frictions[frictionVar];
        // Set new position
        field[i].x += field[i].vx;
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

            case Light:
                lightTexture.blit(p);
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
    window.drawDebugText(10.0, 10.0, "Interactions: \'1-6,0\', Reset: \'r\'");
    switch (type) {
    case Click::None:
        window.drawDebugText(10.0, 25.0, "None");
        break;

    case Click::Push:
        window.drawDebugText(10.0, 25.0, "Push/pull, force: %f", pushForce);
        break;

    case Click::Light:
        window.drawDebugText(10.0, 25.0, "Place light/normal");
        break;

    case Click::Heavy:
        window.drawDebugText(10.0, 25.0, "Place heavy/normal");
        break;

    case Click::Wall:
        window.drawDebugText(10.0, 25.0, "Place wall/normal");
        break;

    case Click::Source:
        window.drawDebugText(10.0, 25.0, "Place source/normal, period: %f", sourceFreq);
        break;

    case Click::Friction:
        window.drawDebugText(10.0, 25.0, "Friction: %f", frictions[frictionVar]);
        break;

    default:
        break;
    }
}
