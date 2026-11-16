#include "platform.h"
#include "../../include/SDL2/SDL_rect.h"
#include "../../include/SDL2/SDL_render.h"
#include "../../include/SDL2/SDL_video.h"
#include <cstdlib>
#include <vector>

#include "../../assets/download/assets.h"
#include "../../plugins/camera/camera.h"
#include "../../code/UI/UI.h"

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

    velocity = 12 + (rand() % 24);

    position.x = Widthwin + (sizex * 64);
    position.y = RowSepare * 64;
    sprite = LoadTexture((PlatformType)(anim));
}

void Platform::Update(float dt, SDL_Window *window, float WorldSpeed, bool Moving, std::vector<Platform> &plat) {
    if (Moving) {
        position.x -= WorldSpeed * dt; 
    }



    if (sprite != Assets::Platforms[6] && sprite != Assets::Platforms[7]) {
        timeleftdt = 0;
        currentFrame = 0;
    } else {
        timeleftdt += dt;
        currentFrame = (int)(timeleftdt * velocity) % 4;
    }

    if (explote) {
        timeleftdtExplote += dt;
        currentFrameExplote = (int)(timeleftdtExplote * 48 / sizex) % 9;

        if (currentFrameExplote == 1) {
            UI::negativeflash = 50 / sizex;
            UI::opacityflash = 50 * sizex;

        }
        if (currentFrameExplote >= 1) {
            sprite = Assets::Platforms[0];
            float dur = 1;
            Camera::shake(dt, 100.0f * sizex, 2.5f * sizex, dur);
        } if (currentFrameExplote >= 8) {
            currentFrameExplote = 0;
            timeleftdtExplote = 0;
            explote = false;
        }
    }

    if (position.x < -128 * sizex) {
        Regenerate(window);
    }



    collide.x = position.x;
    collide.y = position.y;
    collide.w = sizex * 64;

    for (Platform &plats : plat) {
        if (&plats != this && SDL_HasIntersectionF(&collide, &plats.collide)) {
            position.x = plats.position.x + plats.collide.w + 8.0f;
            collide.x = position.x;
        }
    }
}

void Platform::Explote(
    std::vector<Fishoder> &fish,
    std::vector<Shadowner> &shad,
    std::vector<Spikader> &spik,
    std::vector<Platform> &plat
) {

    float expSize = 248.0f * (float)sizex;
    destex = {
        position.x + (sizex * 32.0f) - (expSize / 2.0f),
        position.y + 32.0f - (expSize / 2.0f),
        expSize,
        expSize
    };

    for ( Fishoder &fishoder : fish ) {
        if (SDL_HasIntersectionF(&destex, &fishoder.collide)) {
            fishoder.dead = true;
        }
    }
    for ( Shadowner &shadowner : shad ) {
        if (SDL_HasIntersectionF(&destex, &shadowner.collide)) {
            shadowner.dead = true;
        }
    }
    for ( Platform &platform : plat ) {
        if (&platform != this && platform.sprite == Assets::Platforms[1] && !platform.explote) {
            if (SDL_HasIntersectionF(&destex, &platform.collide)) {
                platform.explote = true;
            }
        }
    }
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

    if (explote) {
        SDL_Rect src = {
            248 * currentFrameExplote, 0, 248, 248
        };

        SDL_FRect dest = {
            (position.x - campos.x) + (sizex * 32.0f) - (248.0f * (float)sizex / 2.0f),
            (position.y - campos.y) + 32.0f - (248.0f * (float)sizex / 2.0f),
            248 * (float)sizex,
            248 * (float)sizex
        };


        SDL_RenderCopyExF(
            render,
            Assets::FX::Explotion,
            &src,
            &dest,
            0,
            NULL,
            SDL_RendererFlip::SDL_FLIP_NONE
        );
    }
}