#ifndef PLAYER_H
#define PLAYER_H

#include "../../include/SDL2/SDL.h"
#include "../../include/SDL2/SDL_events.h"
#include "../../include/SDL2/SDL_rect.h"
#include "../../include/SDL2/SDL_render.h"
#include "../../include/SDL2/SDL_stdinc.h"
#include "../../include/SDL2/SDL_video.h"
#include <vector>
#include "../Platform/platform.h"
#include "../Collectoon/collectoon.h"
#include "../Enemies/Fishoder/fishoder.h"
#include "../Enemies/Shadowner/shadowner.h"
#include "../Enemies/Spikader/spikader.h"

enum class CurrentAnim {
    Idle, Walk, Jump, Fall, Swim, Damage
};

enum class TypeMapping {
    Jump, Stop
};

enum class CurrentAction {
    Fisheated, Normal, Damage, Stoped, Critical, ASKE, Power
};

class Player {
    private:

        static SDL_Texture* sprite;
        static int currentFrame;
        CurrentAnim currentAnim;
        SDL_Texture* lastsprite;
        double timeleftdt;
        static int jumpLeft;
        
        
        static bool InputMapping(SDL_Window* window, const SDL_Event &event, TypeMapping type);
        SDL_Texture* loadTexture(CurrentAnim anim);

    public:

        static float Current_World_Speed;
        static float Apply_World_Speed;

        static float gravity;
        static bool fisheated;
        float fishdur = 0;

        static SDL_FPoint position;
        PlatformType WhatPlatformIs;
        static float Vel_Y;
        static bool stop;
        static bool canStop;

        static bool wasAttacked;
        static bool Dead;
        
        static bool isOnFloor;
        bool inTransporter = false;
        Platform Platforms_map[50];
        static CurrentAction currentAction;

        static float points;
        static float lives;
        static float multiplier;

        static float CooldownDamage; 

        SDL_FRect collide = {70, 72, 58, 134};

        void Create();
        void Update(float dt, SDL_Window* window, SDL_Event event, bool isMoving);

        class Functions {
            public:
            void Draw(SDL_Renderer* render, SDL_FPoint cam);
            static void ActionsAndStuffs(float dt, SDL_Window* window, SDL_Event event, bool isMoving);
        };

        Functions func;

        void CheckCollide(float dt, 
            std::vector<Platform> &platform,
            std::vector<Collectoon> &collectoon
        );
        void CheckCollideEntitys(float dt,
            std::vector<Fishoder> &fish,
            std::vector<Shadowner> &shad,
            std::vector<Spikader> &spik
        );
};

#endif 