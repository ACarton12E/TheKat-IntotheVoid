#pragma once
#include "../../include/SDL2/SDL_rect.h"
#include "../../include/SDL2/SDL_render.h"
#include "../../include/SDL2/SDL_video.h"
#include <cmath>
#include <cstdio>
#include <string>
#include "../../assets/download/assets.h"
#include "../Player/player.h"

class UI {
    public:
        std::string score = "000.000.000";
        std::string multiplier = "0 X";
        std::string aloy = "X 0";

        inline static std::string playerStatus = "Normal";

        inline static float timeleftdt = 0;
        inline static bool eatedFrame = 0;
        inline static float opacityflash = 0;
        inline static float negativeflash = 255;
        inline static float durvalue;


        static void Renderize(
            float dt, 
            SDL_Window* window,
            SDL_Renderer* render,
            float points,
            float lives,
            Player *player
        );
};


inline char* floatToString(float value) {
    static char buffer[32];
    snprintf(buffer, sizeof(buffer), "%.2f", value);
    return buffer;
}

inline char* format(float value) {
    static char buffer[32];

    long long num = std::roundf(value);

    long long M = (num / 100000) % 1000;
    long long k = (num / 1000) % 1000;
    long long u = num % 1000;

    snprintf(buffer, sizeof(buffer), "%03lld.%03lld.%03lld", M, k, u);
    return buffer;
}

inline void UI::Renderize(
    float dt,
    SDL_Window *window, 
    SDL_Renderer *render,
    float points,
    float lives,
    Player *player
) {

    int livesframe = (lives * 8) / 100; 

    int windoww, windowh;

    SDL_GetWindowSize(window, &windoww, &windowh);

    SDL_Rect srcp = {
        0, 0,
        320, 128
    };

    SDL_Rect destp = {
        windoww - 320, 15,
        320, 128
    };

    SDL_RenderCopy(
        render, Assets::UI::Game::PanelPoints, 
        &srcp, 
        &destp
    );

    
    timeleftdt += dt;

    if (player->fisheated) {
        int currentFrameFish = (int)(timeleftdt * 12) % 4;

        SDL_Rect srcfish = {
            160 * currentFrameFish, 0,
            160, 140 
        };  
        float positiony = (float)windowh / 4;

        positiony += cos((timeleftdt * 20) * 0.5);

        SDL_FRect destfish = {
            15, positiony,
            320, 280
        };  

        float rotate = sin((timeleftdt * 20) * 0.5);
    
        SDL_FPoint fishpoint = {160, 140};

        SDL_RenderCopyExF(
            render, 
            Assets::Enemies::Fishoder::Normal, 
            &srcfish, 
            &destfish, 
            rotate, 
            &fishpoint, 
            SDL_FLIP_HORIZONTAL
        );

        if (currentFrameFish == 3 && !eatedFrame) {
            player->lives -= 1;
            eatedFrame = true;
        } else if (currentFrameFish != 3) {
            eatedFrame = false;
        }
    }

    if (opacityflash > 0.0f) {
        opacityflash -= 260.0f * dt;
        if (opacityflash < 0.0f) {
            opacityflash = 0.0f;
        }
    }

    if (negativeflash < 255.0f) {
        negativeflash += 260.0f * dt;
        if (negativeflash > 255.0f) {
            negativeflash = 255.0f;
        }
    }


    SDL_Rect spsrc = {0, 0, 360, 164};
    SDL_FRect spdest = {15, 15, 360, 164};

    SDL_RenderCopyF(render, Assets::UI::Game::Status::StatusPanel, &spsrc, &spdest);

    SDL_Color colortext2 = {255, 255, 255, 255};

    SDL_Surface* surf2 = TTF_RenderText_Solid(Assets::UI::Fonts::uniex_mono, playerStatus.c_str(), colortext2);
    SDL_Texture* text2 = SDL_CreateTextureFromSurface(render, surf2);
    SDL_Rect dest2 = { 27, 27, surf2->w, surf2->h };
    
    SDL_RenderCopy(render, text2, NULL, &dest2);

    SDL_Rect lrsrc = {livesframe * 128, 0, 128, 144};
    SDL_FRect lrdest = {164, 49, 128, 144};

    SDL_RenderCopyF(render, Assets::UI::Game::Status::LiveRoulete, &lrsrc, &lrdest);

    if (player->currentAction == CurrentAction::Fisheated) {
        durvalue = (player->fishdur * 8) / 7;
        playerStatus = "Fisheated!!";
    } else {
        if (!player->Dead) {
            if (player->CooldownDamage >= 0 && player->wasAttacked) {
                durvalue = (player->CooldownDamage * 8) / 1.5;
                playerStatus = "Ouch!!";
            } else {
                durvalue = 0;
                playerStatus = "Normal";
            }
        } else {
            durvalue = 0;
            playerStatus = "Ded :(";
        }
    }

    SDL_Rect drsrc = {(int)durvalue * 128, 0, 128, 144};
    SDL_FRect drdest = {20, 49, 128, 144};

    SDL_RenderCopyF(render, Assets::UI::Game::Status::DurRoulete, &drsrc, &drdest);

    SDL_Rect ersrc = {0, 0, 54, 60};
    SDL_FRect erdest = {95, 138, 54, 60};

    SDL_RenderCopyF(render, Assets::UI::Game::Status::EnergyRoulete, &ersrc, &erdest);

    char buffer[32];

    SDL_Color colortext1 = {255, 255, 255, 255};

        
    SDL_Surface* surf1 = TTF_RenderText_Solid(Assets::UI::Fonts::eas_analog, format(floor(points)), colortext1);
    SDL_Texture* text1 = SDL_CreateTextureFromSurface(render, surf1);

    SDL_Rect dest = { windoww - 280, 25, surf1->w, surf1->h };
    SDL_RenderCopy(render, text1, NULL, &dest);



    SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(render, 255, 255, 255, opacityflash);
    SDL_Rect Rect = {0, 0, windoww, windowh};
    SDL_RenderFillRect(render, &Rect);


    SDL_FreeSurface(surf1);
    SDL_DestroyTexture(text1);
    SDL_FreeSurface(surf2);
    SDL_DestroyTexture(text2);
}
