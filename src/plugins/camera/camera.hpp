#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>


class Camera {
    private:
        int w = 800;
        int h = 600;
    public:
        SDL_FPoint position;
        float zoom = 1.f;
};