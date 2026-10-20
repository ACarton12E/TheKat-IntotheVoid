#ifndef FISHODER_H
#define FISHODER_H

#include "../../../include/SDL2/SDL.h"

class Fishoder {
    private:
        int CurrentFrame = 0;
        float timeleftdt = 0;
    public:
        SDL_FPoint position;
        bool active = true;
        bool dead = false;
        float velocity = 120;
        float rotation = 0;

        SDL_FRect collide = {-1000, -1000, 156, 108};

        void Create(SDL_FPoint pos, bool activated);
        void Update(float dt, SDL_Window* window, float WorldSpeed, bool Moving);
        void Draw(SDL_Renderer* render, SDL_FPoint campos);
        void Regenerate(SDL_Window* window);
        
};

#endif