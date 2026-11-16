#ifndef SHAD_H
#define SHAD_H

#include "../../../include/SDL2/SDL.h"

class Shadowner {
    private:
        float timeleftdt = 0;
        int CurrentFrame = 0;
        SDL_RendererFlip flip = SDL_FLIP_NONE;
    public:
        SDL_FPoint position;
        float rotation;
        bool active = true;
        bool attack = true;
        bool dead = false;
        float toY = 0;
        SDL_FRect collide = {-1000, -1000, 66, 66};

        void Create(SDL_FPoint pos, bool activated);
        void Update(float dt, SDL_Window* window, SDL_FPoint playerPos, float WorldSpeed, bool Moving, bool activePlayer);
        void Draw(SDL_Renderer* render, SDL_FPoint campos);
        void Regenerate(SDL_Window* window);
};

#endif