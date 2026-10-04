#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>
#include <vector>
#include "../Platform/platform.h"
#include "../Collectoon/collectoon.h"

enum class CurrentAnim {
    Idle, Walk, Jump, Fall, Swim
};

enum class TypeMapping {
    Jump, Stop
};

class Player {
    private:

        SDL_Texture* sprite;
        int currentFrame;
        CurrentAnim currentAnim;
        SDL_Texture* lastsprite;
        double timeleftdt;
        int jumpLeft = 2;
        
        
        bool InputMapping(SDL_Window* window, const SDL_Event &event, TypeMapping type);
        SDL_Texture* loadTexture(CurrentAnim anim);

    public:

        float Current_World_Speed = 150.f;
        float gravity = 150.f;
        SDL_FPoint position;
        PlatformType WhatPlatformIs;
        float Vel_Y = 0.f;
        bool stop = false;
        bool canStop = true;
        bool isOnFloor = true;
        bool inTransporter = false;
        Platform Platforms_map[50];

        float points = 0;
        float multiplier = 1;

        SDL_FRect collide = {70, 72, 58, 134};

        void Create();
        void Update(float dt, SDL_Window* window, SDL_Event event, bool isMoving);
        void Draw(SDL_Renderer* render, SDL_FPoint cam);
        void CheckCollide(float dt, 
            std::vector<Platform> &platform,
            std::vector<Collectoon> &collectoon
        );
};

#endif 