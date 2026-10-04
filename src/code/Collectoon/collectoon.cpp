#include "collectoon.h"
#include "../../assets/download/assets.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <cmath>
#include <cstdlib>

SDL_Texture* Collectoon::LoadTexture(CollectoonType ct, FoodType ft) {
    switch (ct) {
        default: switch (ft) {
            case FoodType::Ketchup: return Assets::Collectoon::Food[0]; break;
            case FoodType::Cookie: return Assets::Collectoon::Food[1]; break;
            case FoodType::PotatoMcMaco: return Assets::Collectoon::Food[2]; break;
            case FoodType::ToddyCake: return Assets::Collectoon::Food[3]; break;
            case FoodType::Brocolee: return Assets::Collectoon::Food[4]; break;
            case FoodType::HawaianPizza: return Assets::Collectoon::Food[5]; break;
            case FoodType::Hamburgo: return Assets::Collectoon::Food[6]; break;
            case FoodType::UghFish: return Assets::Collectoon::Food[7]; break;
            case FoodType::ChocoMcMaco: return Assets::Collectoon::Food[8]; break;
            case FoodType::BismolOtpep: return Assets::Collectoon::Food[9]; break;
            case FoodType::Mayo: return Assets::Collectoon::Food[10]; break;
            case FoodType::Guacamole: return Assets::Collectoon::Food[11]; break;
            case FoodType::Kerozink: return Assets::Collectoon::Food[12]; break;
        } break;
    }
    return nullptr;
}

void Collectoon::Create(SDL_FPoint pos, FoodType ft, int cid) {
    position = pos;
    sprite = LoadTexture(CollectoonType::Food, ft);
    id = cid;
}

void Collectoon::Regenerate(SDL_Window* window) {
    int w = 0;

    SDL_GetWindowSize(window, &w, NULL);

    Vel_Y = -250;
    timeleftdt = 0; 
    Katched = false;
    opacity = 255;

    sprite = LoadTexture(CollectoonType::Food, (FoodType)(0 + (rand() % 13)));
    position.y = (-16 + (rand() % 32)) * 64;
    position.x = w;
}

void Collectoon::Update(float dt, SDL_Window *window, float WorldSpeed, bool isMoving) {
    if (isMoving) {
        position.x -= WorldSpeed * dt;
    }


    if (!Katched) {
        timeleftdt += dt;
        position.y += cos((timeleftdt + id) * 12) * 0.5;
    } else {
        Vel_Y += 180 * dt;
        opacity -= 150 * dt;
        position.y += Vel_Y * dt;
    }

    if (position.x < -100) {
        Regenerate(window);
    }

    collide.x = position.x;
    collide.y = position.y;
}

void Collectoon::Draw(SDL_Renderer *render, SDL_FPoint campoint) {
    SDL_FRect destin = {
        position.x - campoint.x,
        position.y - campoint.y,
        32 * 2,
        32 * 2,
    };

    SDL_Rect src = {
        0, 0,
        32, 32
    };
    
    SDL_FPoint origin = {
        0, 0
    };

    SDL_SetTextureAlphaMod(sprite, opacity);

    SDL_RenderCopyExF(
        render, 
        sprite, 
        &src,
        &destin, 
        0, 
        &origin, 
        SDL_FLIP_NONE
    );
    
}