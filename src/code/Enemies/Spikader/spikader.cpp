#include "spikader.h"
#include "../../../assets/download/assets.h"
#include <cmath>

void Spikader::Create(SDL_FPoint pos, bool activated) {
    position = pos;
    active = activated;
}

void Spikader::Regenerate(SDL_Window *window) {
    int w = 0;
    SDL_GetWindowSize(window, &w, NULL);

    active = ((rand() % 100) < 40);
    timeleftdt = 0;
    position.x = w;
    position.y = (float)(-16 + (rand() % 32)) * 104;
}

void Spikader::Update(float dt, SDL_Window *window, float WorldSpeed, bool Moving) {
    if (Moving) {
        position.x -= WorldSpeed * dt;
    }

    timeleftdt += dt;
    CurrentFrame = (int)(timeleftdt * 12) % 4;

    position.y += cos(timeleftdt * 10) * 0.5;

    if (position.x < -100) {
        Regenerate(window);
    }

    collide.x = position.x;
    collide.y = position.y;
}

void Spikader::Draw(SDL_Renderer *render, SDL_FPoint campos) {
    SDL_Rect src = {
        52 * CurrentFrame, 0,
        52, 52
    };

    SDL_FRect dest = {
        position.x - campos.x, position.y - campos.y,
        52 * 2, 52 * 2
    };

    if (active) {
        SDL_RenderCopyF(
            render, 
            Assets::Enemies::Spikader::Normal, 
            &src, 
            &dest
        );
    }
}