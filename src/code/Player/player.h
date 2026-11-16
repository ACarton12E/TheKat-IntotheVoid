#ifndef PLAYER_H
#define PLAYER_H

#include "../../include/SDL2/SDL_events.h"
#include "../../include/SDL2/SDL_rect.h"
#include "../../include/SDL2/SDL_render.h"
#include "../../include/SDL2/SDL_video.h"
#include <vector>
#include "../Platform/platform.h"
#include "../Collectoon/collectoon.h"
#include "../Enemies/Fishoder/fishoder.h"
#include "../Enemies/Shadowner/shadowner.h"
#include "../Enemies/Spikader/spikader.h"
#include "../Water/water.h"
#include "../../plugins/particles/particle.h"

enum class CurrentAnim {
    Idle, Walk, Jump, Fall, Swim, Flying, BadFlying, SplashFloor, Damage
};

enum class TypeMapping {
    Jump, Stop, Fly
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

        struct ArmorHand {
            static float rotation;
            static SDL_FPoint position;
            inline static SDL_FRect collideS = {0.0f, 0.0f, 0.0f, 0.0f};

            static float cooldoown;

            static ParticleSys* particle;
            static bool isShootingFire;

            static void Update(float dt, SDL_Window* window, SDL_Event event, SDL_FPoint campos);
            static void Render(SDL_Renderer* render, SDL_FPoint campos);
            static void Shoot(
                std::vector<Fishoder> &fishs,
                std::vector<Shadowner> &shads,
                std::vector<Spikader> &spiks,
                std::vector<Platform> &plats,
                SDL_Window* window);
        };

        ArmorHand armors;

        static float Current_World_Speed;
        static float Apply_World_Speed;

        static float gravity;
        static bool fisheated;
        float fishdur = 0;
        static bool AskeMode;

        static SDL_FPoint position;
        PlatformType WhatPlatformIs;
        static float Vel_Y;
        static float rotation;
        static bool stop;
        static bool canStop;

        static bool wasAttacked;
        static bool Dead;
        static bool inWater;
        static bool flying;
        static bool iCanFlyBTW;
        
        static bool isOnFloor;
        bool inTransporter = false;
        Platform Platforms_map[50];
        static CurrentAction currentAction;

        static float points;
        static float lives;
        static float multiplier;

        float multiplierdur = 0.0f;

        static float CooldownDamage; 

        SDL_FRect collide = {70.0f, 72.0f, 58.0f, 134.0f};
        static SDL_FPoint SizeSprite;

        void Create();
        void Update(float dt, SDL_Window* window, SDL_Event event, bool isMoving, SDL_FPoint campos);

        class Functions {
            public:
            void Draw(SDL_Renderer* render, SDL_FPoint cam);
            static void ActionsAndStuffs(float dt, SDL_Window* window, SDL_Event event, bool isMoving, SDL_FPoint campos);
            static void WaterOrSuper(float dt, SDL_Window* window, SDL_Event event, SDL_FPoint campos);
        };

        Functions func;

        void CheckCollide(float dt, 
            std::vector<Platform> &platform,
            std::vector<Collectoon> &collectoon,
            std::vector<Water> &water
        );
        void CheckCollideEntitys(float dt,
            std::vector<Fishoder> &fish,
            std::vector<Shadowner> &shad,
            std::vector<Spikader> &spik
        );
};


#endif 