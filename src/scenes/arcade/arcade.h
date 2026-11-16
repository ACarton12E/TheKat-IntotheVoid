#ifndef ARCADE_H
#define ARCADE_H

#include <vector>
#include "../../code/Collectoon/collectoon.h"
#include "../../code/Platform/platform.h"
#include "../../code/Player/player.h"
#include "../../code/Enemies/Fishoder/fishoder.h"
#include "../../code/Enemies/Shadowner/shadowner.h"
#include "../../code/Enemies/Spikader/spikader.h"
#include "../../code/Water/water.h"

class ArcadeScene {
    public:
        Player player;
        static std::vector<Platform> platforms_map;
        static std::vector<Collectoon> collectoon_map;

        static std::vector<Fishoder> fishoder_entitys;
        static std::vector<Shadowner> shadowner_entitys;
        static std::vector<Spikader> spikader_entitys;

        static std::vector<Water> water_map;

        void generate();
        bool isMoving(bool Stop, bool onFloor, PlatformType CurrentPlat);

        void Update(
            float dt, SDL_Event event, 
            SDL_Window* window, 
            SDL_Renderer* render, 
            SDL_FPoint &playerpos,
            float &WorldSpeed,
            SDL_FPoint cam
        );

        void Render(
            float dt, SDL_Event event, SDL_Window* window, SDL_Renderer* render, SDL_FPoint cam
        );
};

#endif