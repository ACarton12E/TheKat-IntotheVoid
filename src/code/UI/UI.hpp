#pragma once
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <string>
#include "../../assets/download/assets.h"

class UI {
    public:
        std::string score = "000.000.000";
        std::string multiplier = "0 X";
        std::string aloy = "X 0";

        std::string playerStatus = "Normal";

        static void Renderize(SDL_Window* window, SDL_Renderer* render);
};

inline void UI::Renderize(SDL_Window *window, SDL_Renderer *render) {

    SDL_Rect srcp = {
        0, 0,
        320, 128
    };

    SDL_Rect destp = {
        0, 0,
        320, 128
    };

    SDL_RenderCopy(
        render, Assets::UI::Game::PanelPoints, 
        &srcp, 
        &destp
    );
}