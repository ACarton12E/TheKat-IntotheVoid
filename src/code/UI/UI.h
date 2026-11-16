#pragma once
#include "../../include/SDL2/SDL_rect.h"
#include "../../include/SDL2/SDL_render.h"
#include "../../include/SDL2/SDL_video.h"
#include <cmath>
#include <cstdio>
#include <string>
#include "../../assets/download/assets.h"
#include "../Player/player.h"

enum class ToSCENES {
    MENU, ARCADE
};

class UI {
    private:
        static SDL_Texture* textState;
        static std::string lastState;
        static SDL_Rect destState;

        static SDL_Texture* textPoints;
        static long long lastPoints;
        static SDL_Rect destPoints;

        static SDL_Texture* textMultp;
        static float lastMultp;
        static SDL_Rect destMultp;
    public:
        std::string score = "000.000.000";
        std::string multiplier = "0 X";
        std::string aloy = "X 0";

        static std::string playerStatus;

        static float timeleftdt;
        static bool eatedFrame;
        static float opacityflash;
        static float negativeflash;
        static float durvalue;

        static void Preload(SDL_Renderer *render);

        static void Renderize(
            float dt, 
            SDL_Event event,
            SDL_Window* window,
            SDL_Renderer* render,
            float points,
            float lives,
            Player *player
        );
        static void Clean();
};
 