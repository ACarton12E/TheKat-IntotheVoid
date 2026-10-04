#ifndef PLATFORM_H
#define PLATFORM_H

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

enum class PlatformType {
    Normal, Oil, 
    Honey, Ice, 
    Spikader, Trampoder, 
    TranspRight, TranspLeft
};

class Platform {
    private:
        
        int currentFrame = 0;
        float timeleftdt = 0;
    public:
        
        SDL_FPoint position;
        int sizex;
        SDL_Texture* sprite;

        SDL_FRect Collide = {0, 0, 64, 64};

        SDL_Texture* LoadTexture(PlatformType type);
        void Create(SDL_FPoint pos, PlatformType type, int sizexn);
        void Update(float dt, SDL_Window* window, float WorldSpeed, bool Moving);
        void Draw(SDL_Renderer* render, SDL_FPoint campos);
        void Regenerate(SDL_Window* window);
};

#endif