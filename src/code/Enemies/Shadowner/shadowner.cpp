#include "shadowner.h"
#include "../../../assets/download/assets.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>

void Shadowner::Create(SDL_FPoint pos, bool activated) {
    position = pos;
    active = activated;
}

void Shadowner::Regenerate(SDL_Window *window) {
    int w = 0;
    SDL_GetWindowSize(window, &w, NULL);
    active = ((rand() % 100) < 20);
    timeleftdt = 0;
    attack = true;
    collide.y = -1000;
    position = {
        (float)w, (float)(-16 + (rand() % 32)) * 128
    };
}

void Shadowner::Update(float dt, SDL_Window *window, SDL_FPoint playerPos, float WorldSpeed, bool Moving, bool activePlayer) {
    if (Moving) {
        position.x -= WorldSpeed * dt;
    }


    timeleftdt += dt;
    CurrentFrame = (int)(timeleftdt * 12) % 4;

    int dx = playerPos.x - position.x;
    int dy = playerPos.y - position.y;

    float atan = atan2(dy, dx);
    float distance = sqrt(pow(dx, 2) + pow(dy, 2));

    if (attack && active) {
        if (distance < 400 && activePlayer) {
            rotation += (((atan * (180 / M_PI)) + 180) - rotation) * (20 * dt);
            position.x += (cos(atan) * 240) * dt;
            position.y += (sin(atan) * 240) * dt;
        } else {
            rotation += ((0 + (sin(timeleftdt * 12) * 0.5)) - rotation) * (20 * dt);
            position.y += cos(timeleftdt * 12) * 0.5;
        }
    } else {
        position.x -= 150 * dt;
        flip = SDL_FLIP_NONE;
        rotation = 0;
    }

    float normalizedRotation = rotation;
    while (normalizedRotation > 180.0f)  normalizedRotation -= 360.0f;
    while (normalizedRotation < -180.0f) normalizedRotation += 360.0f;

    if (normalizedRotation > -90.0f && normalizedRotation < 90.0f) {
        flip = SDL_FLIP_NONE;
    } else {
        flip = SDL_FLIP_VERTICAL;
    }

    if (position.x < -228) {
        Regenerate(window);
    }
    collide.x = position.x + 44;
    collide.y = position.y + 32;

}

void Shadowner::Draw(SDL_Renderer *render, SDL_FPoint campos) {
    SDL_Rect src = {
        96 * CurrentFrame, 0,
        96, 64
    };

    SDL_FRect dest = {
        position.x - campos.x, position.y - campos.y,
        96 * 2, 64 * 2
    };

    SDL_FPoint cent = {96, 64};

    if (active) {
        SDL_RenderCopyExF(
            render, 
            Assets::Enemies::Shadowner::Normal, 
            &src, 
            &dest, 
            rotation, 
            &cent, 
            flip
        );
    }   
}