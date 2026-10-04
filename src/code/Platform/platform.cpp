#include "platform.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <cstdlib>

#include "../../assets/download/assets.h"

SDL_Texture* Platform::LoadTexture(PlatformType type) {
    switch (type) {
        case PlatformType::Normal: return Assets::Platforms[0];
        case PlatformType::Oil: return Assets::Platforms[1];
        case PlatformType::Honey: return Assets::Platforms[2];
        case PlatformType::Ice: return Assets::Platforms[3];
        case PlatformType::Spikader: return Assets::Platforms[4];
        case PlatformType::Trampoder: return Assets::Platforms[5];
        case PlatformType::TranspRight: return Assets::Platforms[6];
        case PlatformType::TranspLeft: return Assets::Platforms[7];
    }
}

void Platform::Create(SDL_FPoint pos, PlatformType type, int sizexn) {
    position = pos;
    sprite = LoadTexture(type);
    sizex = sizexn;
}

void Platform::Regenerate(SDL_Window* window) {
    
    sizex = 1 + (rand() % 5);

    int Widthwin;

    SDL_GetWindowSize(window, &Widthwin, NULL);

    int anim = 0;

    if (rand() % 100 < 30) {
        anim = 0 + (rand() % 8);
    } else {
        anim = 0;
    }

    int RowRandi = -5 + (rand() % 11);
    int RowSepare = RowRandi * 2;

    position.x = Widthwin + (sizex * 64);
    position.y = RowSepare * 64;
    sprite = LoadTexture((PlatformType)(anim));
}

void Platform::Update(float dt, SDL_Window *window, float WorldSpeed, bool Moving) {
    if (Moving) {
        position.x -= WorldSpeed * dt; 
    }



    if (sprite != Assets::Platforms[6] && sprite != Assets::Platforms[7]) {
        timeleftdt = 0;
        currentFrame = 0;
    } else {
        timeleftdt += dt;
        currentFrame = (int)(timeleftdt * 12) % 4;
    }

    if (position.x < -128 * sizex) {
        Regenerate(window);
    }


    Collide.x = position.x;
    Collide.y = position.y;
    Collide.w = sizex * 64;
}

void Platform::Draw(SDL_Renderer *render, SDL_FPoint campos) {
    for (int i = 0; i < sizex; i++) {

        SDL_Rect src = {
            32 * currentFrame, 0,
            32,
            32
            
        };
        SDL_FRect dest = {
            (position.x - campos.x) + (i * 64),
            position.y - campos.y,
            32 * 2,
            32 * 2
        };

        SDL_FPoint point = {
            0,
            0
        };

        SDL_RenderCopyExF(
            render, 
            sprite, 
            &src, 
            &dest, 
            0, 
            &point, 
            SDL_RendererFlip::SDL_FLIP_NONE
        );
    }
}