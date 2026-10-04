#ifndef COLLECTOON_H
#define COLLECTOON_H

#include "SDL2/SDL.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include "../Platform/platform.h"

enum class CollectoonType {
    Food, Disk, Aloy, Power
};

enum class FoodType {
    Ketchup, Cookie, PotatoMcMaco, ToddyCake, Brocolee, HawaianPizza, Hamburgo, 
    UghFish, ChocoMcMaco, BismolOtpep, Mayo, Guacamole, Kerozink
};

class Collectoon {
    private:
        SDL_Texture* sprite;
        CollectoonType type;
        float timeleftdt;
        Uint8 opacity = 255;
    public:
        SDL_FPoint position;
        int id = 0;
        SDL_FRect collide = {0, 0, 32, 32};
        bool Katched = false;
        float Vel_Y = -250;
    
        SDL_Texture* LoadTexture(CollectoonType ct, FoodType ft);

        void Create(SDL_FPoint pos, FoodType ft, int cid);
        void Update(float dt, SDL_Window *window, float WorldSpeed, bool isMoving);
        void Draw(SDL_Renderer* render, SDL_FPoint campoint);
        void Regenerate(SDL_Window* window);
};

#endif