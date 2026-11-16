#ifndef PLATFORM_H
#define PLATFORM_H

#include "../../include/SDL2/SDL_rect.h"
#include "../../include/SDL2/SDL_render.h"

#include "../../code/Enemies/Fishoder/fishoder.h"
#include "../../code/Enemies/Shadowner/shadowner.h"
#include "../../code/Enemies/Spikader/spikader.h"

#include <vector>

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

        int currentFrameExplote = 0;
        float timeleftdtExplote = 0;

        SDL_FRect destex {0, 0, 0, 0};
    public:
        
        float velocity = 12;
        
        SDL_FPoint position;
        int sizex;
        SDL_Texture* sprite;
        bool explote = false;

        SDL_FRect collide = {-1000, -1000, 64, 64};

        SDL_Texture* LoadTexture(PlatformType type);
        void Create(SDL_FPoint pos, PlatformType type, int sizexn);
        void Update(float dt, SDL_Window* window, float WorldSpeed, bool Moving, std::vector<Platform> &plat);
        void Draw(SDL_Renderer* render, SDL_FPoint campos);
        void Regenerate(SDL_Window* window);
        void Explote(
            std::vector<Fishoder> &fish,
            std::vector<Shadowner> &shad,
            std::vector<Spikader> &spik,
            std::vector<Platform> &plat
        );
};

#endif