#pragma once
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <cmath>
#include <cstdio>
#include <string>
#include "../../assets/download/assets.h"

class UI {
    public:
        std::string score = "000.000.000";
        std::string multiplier = "0 X";
        std::string aloy = "X 0";

        std::string playerStatus = "Normal";

        static void Renderize(SDL_Window* window, 
            SDL_Renderer* render,
            float points
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
    SDL_Window *window, 
    SDL_Renderer *render,
    float points
) {


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


    char buffer[32];

    SDL_Color colortext1 = {255, 255, 255, 255};
    SDL_Color colortext2 = {0, 50, 0, 255};
        
    SDL_Surface* surf1 = TTF_RenderText_Solid(Assets::UI::Fonts::eas_analog, format(floor(points)), colortext1);
    SDL_Texture* text1 = SDL_CreateTextureFromSurface(render, surf1);
    SDL_Surface* surf2 = TTF_RenderText_Solid(Assets::UI::Fonts::eas_analog, "000.000.000", colortext2);
    SDL_Texture* text2 = SDL_CreateTextureFromSurface(render, surf2);

    SDL_Rect dest = { windoww - 280, 25, surf1->w, surf1->h };
    SDL_RenderCopy(render, text1, NULL, &dest);
    /*SDL_Rect dest2 = { windoww - 290, 20, surf2->w, surf2->h };
    SDL_RenderCopy(render, text2, NULL, &dest2);*/

    SDL_FreeSurface(surf1);
    SDL_DestroyTexture(text1);
    SDL_FreeSurface(surf2);
    SDL_DestroyTexture(text2);
}
