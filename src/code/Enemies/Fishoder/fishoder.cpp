#include "fishoder.h"
#include "../../../assets/download/assets.h"
#include <cmath>
#include <cstdlib>

void Fishoder::Create(SDL_FPoint pos, bool activated) {
    position = pos;
    active = activated;
} 

void Fishoder::Regenerate(SDL_Window *window) {
    int w = 0;
    SDL_GetWindowSize(window, &w, NULL);
    timeleftdt = 0;
    active = ((rand() % 100) < 20);
    velocity = ((rand() % 100) < 70) ? 120 : 250;
    collide.y = -1000;
    dead = false;
    velocityY = -velocity;
    rotation = 0; 
    position = {
        (float)w, (float)(-16 + (rand() % 32)) * 280
    };
}

void Fishoder::Update(float dt, SDL_Window *window, float WorldSpeed, bool Moving) {
    if (Moving) {
        position.x -= (velocity + WorldSpeed) * dt;
    } else {
        position.x -= velocity * dt;
    }

    timeleftdt += dt;

    CurrentFrame = (int)(timeleftdt * 12) % 4;

    if (!dead) {
        position.y += cos(timeleftdt * (velocity / 12)) * 0.5;
        rotation += sin(timeleftdt * (velocity / 12)) * 0.5;
    } else {
        rotation -= velocity * dt;
        velocityY += 120 * dt;
        position.y += velocityY * dt;
    }

    if (position.x < -165) {
        Regenerate(window);
    }

    collide.x = position.x + 86;
    collide.y = position.y + 108;
}

void Fishoder::Draw(SDL_Renderer *render, SDL_FPoint campos) {
    SDL_Rect src = {
        160 * CurrentFrame, 0,
        160, 140
    };

    SDL_FRect dest = {
        position.x - campos.x, position.y - campos.y,
        160 * 2, 140 * 2
    };

    SDL_FPoint point = {160, 140};

    if (active) {
        SDL_RenderCopyExF(
            render, 
            Assets::Enemies::Fishoder::Normal, 
            &src, 
            &dest,
            rotation,
            &point,
            SDL_FLIP_NONE
        );
    }
}