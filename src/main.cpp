#include "include/SDL2/SDL_events.h"
#include "include/SDL2/SDL_gamecontroller.h"
#include "include/SDL2/SDL_mixer.h"
#include "include/SDL2/SDL_rect.h"
#include "include/SDL2/SDL_render.h"
#include "include/SDL2/SDL_timer.h"
#include "include/SDL2/SDL_ttf.h"
#include "include/SDL2/SDL_video.h"
#include "include/SDL2/SDL.h"
#include <cstdlib>
#include <iostream>
#include <vector>

#include "assets/download/assets.h"
#include "plugins/camera/camera.hpp"
#include "plugins/betterInit/betterInit.hpp"
#include "plugins/betterInput/betterInput.hpp"

#include "code/Collectoon/collectoon.h"
#include "code/Platform/platform.h"
#include "code/Player/player.h"
#include "code/Enemies/Fishoder/fishoder.h"
#include "code/Enemies/Shadowner/shadowner.h"
#include "code/Enemies/Spikader/spikader.h"

#include "code/UI/UI.hpp"


bool isMoving(bool Stop, bool onFloor, PlatformType CurrentPlat) {
    

    if (onFloor) {
        
        if (CurrentPlat == PlatformType::TranspLeft) {
            return true;
        }
        
        else if (CurrentPlat == PlatformType::TranspRight) {
            return true;
        } else if (CurrentPlat != PlatformType::TranspRight && CurrentPlat != PlatformType::TranspLeft) {
            if (!Stop) {
                return true;
            }
        }

    } else {
        if (CurrentPlat != PlatformType::TranspRight && CurrentPlat != PlatformType::TranspRight) {
            if (!Stop) {
                return true;
            }
        } else if (CurrentPlat == PlatformType::TranspRight || CurrentPlat == PlatformType::TranspLeft) {
            if (!Stop) {
                return true;
            }
        }
    }

    return false;
}

std::vector<Platform> platforms_map(50);
std::vector<Collectoon> collectoon_map(70);

std::vector<Fishoder> fishoder_entitys(14);
std::vector<Shadowner> shadowner_entitys(14);
std::vector<Spikader> spikader_entitys(14);

void generate(Player &player) {

    player.position = {0.0f, 0.0f};
    player.Vel_Y = 0.0f;
    player.lives = 100.0f;
    player.points = 0.0f;
    player.multiplier = 1.0f;
    player.Apply_World_Speed = 150.0f;
    player.Current_World_Speed = 150.0f;
    player.stop = false;
    player.canStop = false;
    player.isOnFloor = false;
    player.fisheated = false;
    player.CooldownDamage = 0.0f;
    player.wasAttacked = false;
    player.Dead = false;
    player.currentAction = CurrentAction::Normal;

    UI::timeleftdt = 0;
    UI::opacityflash = 0;
    UI::eatedFrame = false;

    for (int i = 0; i < platforms_map.size(); i++) {
        int anim = 0;
        int ix3 = i + 3;

        if (rand() % 100 < 30) {
            anim = 0 + (rand() % 8);
        } else {
            anim = 0;
        }

        int RowRandi = -5 + (rand() % 11);
        int RowSepare = RowRandi * 2;

        platforms_map[i].Create(
            {
                (float)i * 64,
                (float)RowSepare * 64
            }, 
                (PlatformType)anim, 
            3 + (rand() % 8)
        );
    }

    for (int i = 0; i < collectoon_map.size(); i++) {
        int anim = 0;
        anim = 0 + (rand() % 13);

        collectoon_map[i].Create(
            {
                (float)i * 64,
                (float)(-16 + (rand() % 32)) * 64
            }, 
                (FoodType)anim,
                1 + i
        );
    }

    for (int i = 0; i < fishoder_entitys.size(); i++) {

        bool activated = ((rand() % 100) < 30);

        fishoder_entitys[i].Create(
            {
                (float)i * 320,
                (float)(-16 + (rand() % 32)) * 280
            }, 
            activated
        );
    };

    for (int i = 0; i < shadowner_entitys.size(); i++) {
        bool activated = ((rand() % 100) < 30);

        shadowner_entitys[i].Create(
            {
                (float)i * 184,
                (float)(-16 + (rand() % 32)) * 128
            }, 
            activated
        );
    }

    for (int i = 0; i < spikader_entitys.size(); i++) {
        bool activated = ((rand() % 100) < 30);

        spikader_entitys[i].Create(
            {
                (float)i * 104,
                (float)(-16 + (rand() % 32)) * 104
            }, 
            activated
        );
    }
}

int main(int argc, char **argv) {

    SDL_GameController* pad;
    SDL_Window* window;
    SDL_Renderer* render;

    if (TTF_Init() == -1) {
        std::cerr << "Oh, the Font! Uhhh " << TTF_GetError() << std::endl;
    }   

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 0, 2048) < 0) {
        std::cerr << "Oh, the Audio! Uhhh " << Mix_GetError() << std::endl;
    }

    int Audio = Mix_Init(MIX_INIT_OGG);

    
    int result = BetterInit::loadSDLwithGamepad(
        WindowConfig {
            "The Kat - Clangs Into the Void!",
            1280,
            720,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE,
            Assets::icon
        }, 
        RenderConfig {
            -1,
            SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED
        }, 
        pad, 
        window, 
        render
    );

    if (result != 0) {
        return result;
    }

    Assets::LoadAll(render);
    srand(time(NULL)); 

    
    Mix_PlayMusic(Assets::Musics::IntotheVoid, -1);

    Player player;
    player.Create();

    generate(player);

    bool loopithing = true;
    SDL_Event event;

    bool moving = false;

    Camera cam;
    float xtest;

    cam.zoom = 1.5;

    double dt = 0.0;
    Uint32 last_time = SDL_GetTicks();
    int desplX = 0;

    while (loopithing) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                loopithing = false;
            }
        }

        if (BetterInput::Keyboard::onJustPressed(event, SDL_SCANCODE_R)) {
            generate(player);
        }

        Uint32 current_time = SDL_GetTicks();
        dt = (current_time - last_time) / 1000.0; 
        last_time = current_time;

        //xtest += 20 * dt;
        cam.position.x += (player.position.x - cam.position.x) * (dt * 5);
        cam.position.y += ((player.position.y - 250.0f) - cam.position.y) * (dt * 5);

        bool fisheated = player.fisheated;

        SDL_SetRenderDrawColor(render, 0, 0, 0, 255);   
        SDL_RenderClear(render);

        player.Update(dt, window, event, moving);

        if (!fisheated && !player.Dead) {
            player.CheckCollide(dt, platforms_map, collectoon_map);
            player.CheckCollideEntitys(dt, fishoder_entitys, shadowner_entitys, spikader_entitys);
        }
        moving = isMoving(player.stop, player.isOnFloor, player.WhatPlatformIs);

        for (Platform &platforms : platforms_map) platforms.Update(dt, window, player.Current_World_Speed, moving);
        for (Collectoon &collectoons : collectoon_map) collectoons.Update(dt, window, player.Current_World_Speed, moving);
        for (Shadowner &shad : shadowner_entitys) shad.Update(dt, window, player.position, player.Current_World_Speed, moving, (!fisheated && player.CooldownDamage <= 0));
        for (Fishoder &fish : fishoder_entitys) fish.Update(dt, window, player.Current_World_Speed, moving);
        for (Spikader &spiky : spikader_entitys) spiky.Update(dt, window, player.Current_World_Speed, moving);

        if (player.position.y > 2500) {
            generate(player);
        }

        int texW = 0, texH = 0;
        SDL_QueryTexture(Assets::Background, NULL, NULL, &texW, &texH);

        if (!moving) {
            desplX += (80) * dt;
        } else {
            desplX += (((player.Current_World_Speed / 5) + 80) ) * dt;
        }
        int desplY = ((int)(cam.position.y / 5)) % (texH * 2);

        if (desplX < 0) desplX += texW * 2;
        if (desplY < 0) desplY += texH * 2;

        for (int y = -desplY; y < 1200; y += texH * 2) {
            for (int x = -desplX; x < 1600; x += texW * 2) {
                
                SDL_Rect srcback = {
                    0, 0,
                    texW, texH
                };

                SDL_Rect destback = {
                    x, y,
                    texW * 2, texH * 2
                };

                SDL_Point center = {0, 0};

                SDL_RenderCopyEx(
                    render, 
                    Assets::Background, 
                    &srcback, 
                    &destback, 
                    0, 
                    &center, 
                    SDL_FLIP_NONE
                );
            }
        }

        for (Platform &platforms : platforms_map) platforms.Draw(render, cam.position);
        for (Collectoon &collectoons : collectoon_map) collectoons.Draw(render, cam.position);
        for (Shadowner &shad : shadowner_entitys) shad.Draw(render, cam.position);
        for (Spikader &spiky : spikader_entitys) spiky.Draw(render, cam.position);
        for (Fishoder &fish : fishoder_entitys) fish.Draw(render, cam.position);
        

        UI::Renderize(dt, window, render, player.points, player.lives, &player);

        if (!fisheated) {
            player.func.Draw(render, cam.position);
        }

        


        SDL_RenderPresent(render);
    }

    BetterInit::unloadSDLwithGamepad(render, window, pad);
    Mix_CloseAudio();
    Mix_Quit();
    TTF_CloseFont(Assets::UI::Fonts::eas_analog);
    TTF_CloseFont(Assets::UI::Fonts::monogram_ext);
    TTF_CloseFont(Assets::UI::Fonts::uniex_mono);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
