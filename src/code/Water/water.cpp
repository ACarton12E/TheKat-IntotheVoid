#include "water.h"
#include "../../assets/download/assets.h"

void Water::Create(SDL_FPoint pos) {
    position = pos;
}

void Water::Regenerate(SDL_Window* window) {
    int w;
    SDL_GetWindowSize(window, &w, NULL);
    timeleftdt = 0;

    position = {
        (float)w, (float)(-16 + (rand() % 32)) * 128
    };
}

void Water::Update(float dt, SDL_Window* window, float WorldSpeed, bool Moving) {
    if (Moving) {
        position.x -= WorldSpeed * dt;
    }

    timeleftdt += dt;
    CurrentFrame = (int)(timeleftdt * 12) % 4;

    if (position.x < -440) {
        Regenerate(window);
    }

    collide.x = position.x + 44;
    collide.y = position.y + 40;
}

void Water::Draw(SDL_Renderer* render, SDL_FPoint campos) {
    SDL_Rect src = {
        228 * CurrentFrame, 0,
        228, 128
    };

    SDL_FRect dest = {
        position.x - campos.x, position.y - campos.y,
        228 * 2, 128 * 2
    };

    SDL_RenderCopyF(render, Assets::Water::Normal, &src, &dest);
}