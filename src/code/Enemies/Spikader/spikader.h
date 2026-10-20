#ifndef SPIKADER_H
#define SPIKADER_H

#include "../../../include/SDL2/SDL.h"

class Spikader {
    private:
        float timeleftdt = 0;
        int CurrentFrame = 0;
    public:
        SDL_FPoint position;
        bool active;
        SDL_FRect collide = {0, 0, 104, 104};

        void Create(SDL_FPoint pos, bool activated);
        void Update(float dt, SDL_Window* window, float WorldSpeed, bool Moving);
        void Draw(SDL_Renderer* render, SDL_FPoint campos);
        void Regenerate(SDL_Window* window);
};

#endif