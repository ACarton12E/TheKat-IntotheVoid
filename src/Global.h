#pragma once
#include "include/SDL2/SDL.h"
#include <string>

enum class SCENES {ARCADE, MENU};


class Global {
    public:
        
        static float Score;
        inline static int CurrentArmor = 5;
        static SCENES CurrentScene;
        int Aloy;

        struct ArmorData {
            inline static std::string name = "";
            inline static float size = 0;
            inline static float cooldown = 0;
            inline static bool canPressed;
            struct Particles {
                inline static bool active = false;
                inline static bool fire = false;
                inline static SDL_Texture* assets = nullptr;
                inline static int count = 0;
            };
        };
};
