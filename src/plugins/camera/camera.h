#pragma once
#include "../include/SDL2/SDL_rect.h"

class Camera {
    private:
        int w = 800;
        int h = 600;

        static inline SDL_FPoint lastOffset = {0.0f, 0.0f};
    public:
        static inline SDL_FPoint position = {0.0f, 0.0f};
        static inline float zoom = 1.f;
        static inline float elapsedTime = 0.0f;


        static void shake(float dt, float freq, float amp, float& dur);
};