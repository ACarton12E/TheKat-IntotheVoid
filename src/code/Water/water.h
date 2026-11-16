#ifndef WATER_H
#define WATER_H

#include "../../include/SDL2/SDL.h"

class Water
{
private:
    int CurrentFrame = 0;
    float timeleftdt = 0;
public:
    SDL_FPoint position;
    SDL_FRect collide = {0, 0, 362, 176};

    void Create(SDL_FPoint pos);
    void Update(float dt, SDL_Window* window, float WorldSpeed, bool Moving);
    void Draw(SDL_Renderer* render, SDL_FPoint campos);
    void Regenerate(SDL_Window* window);
};

#endif
