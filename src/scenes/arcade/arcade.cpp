#include "arcade.h"
#include "../../plugins/betterInput/betterInput.hpp"
#include "../../code/UI/UI.h"
#include <vector>
#include "../../Global.h"
#include "../../plugins/camera/camera.h"
#include <math.h>

std::vector<Platform> ArcadeScene::platforms_map(50);
std::vector<Collectoon> ArcadeScene::collectoon_map(70);

std::vector<Fishoder> ArcadeScene::fishoder_entitys(14);
std::vector<Shadowner> ArcadeScene::shadowner_entitys(14);
std::vector<Spikader> ArcadeScene::spikader_entitys(14);

std::vector<Water> ArcadeScene::water_map(8);

float cooldown = 0;

bool ArcadeScene::isMoving(bool Stop, bool onFloor, PlatformType CurrentPlat) {
    

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


void ArcadeScene::generate() {

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
    UI::opacityflash = 255;
    UI::negativeflash = 0;
    UI::eatedFrame = false;

    player.Create();

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

    for (int i = 0; i < water_map.size(); i++) {
        water_map[i].Create(
            {
                (float)i * 228,
                (float)(-16 + (rand() % 32)) * 128
            }
        );
    }
}


void ArcadeScene::Update(float dt, SDL_Event event, SDL_Window *window, SDL_Renderer *render, SDL_FPoint &playerpos, float &WorldSpeed, SDL_FPoint cam) {
    if (BetterInput::Keyboard::onJustPressed(event, SDL_SCANCODE_R)) {
        generate();
    }

    bool fisheated = player.fisheated;
    bool moving = isMoving(player.stop, player.isOnFloor, player.WhatPlatformIs);
    player.Update(dt, window, event, moving, cam);

    if (!fisheated && !player.Dead) {
        player.CheckCollide(dt, platforms_map, collectoon_map, water_map);
        player.CheckCollideEntitys(dt, fishoder_entitys, shadowner_entitys, spikader_entitys);
    }
        
    playerpos = player.position;
    WorldSpeed = player.Current_World_Speed;

    if (player.position.y > 2500) {
        generate();
    }



    for (Platform &platforms : platforms_map) platforms.Update(dt, window, player.Current_World_Speed, moving, platforms_map);
    for (Collectoon &collectoons : collectoon_map) collectoons.Update(dt, window, player.Current_World_Speed, moving);
    for (Shadowner &shad : shadowner_entitys) shad.Update(dt, window, player.position, player.Current_World_Speed, moving, (!fisheated && player.CooldownDamage <= 0));
    for (Fishoder &fish : fishoder_entitys) fish.Update(dt, window, player.Current_World_Speed, moving);
    for (Spikader &spiky : spikader_entitys) spiky.Update(dt, window, player.Current_World_Speed, moving);
    for (Water &wat : water_map) wat.Update(dt, window, player.Current_World_Speed, moving);

    if (player.AskeMode) {
        if (cooldown <= 0) {


            if (!Global::ArmorData::Particles::fire && !Global::ArmorData::canPressed) {
                if (BetterInput::Mouse::onJustPressed(event, SDL_BUTTON_LEFT)) {
                    player.armors.Shoot(fishoder_entitys, shadowner_entitys, spikader_entitys, platforms_map, window);
                    cooldown = Global::ArmorData::cooldown;
                }
            } else {
                if (BetterInput::Mouse::onPressed(SDL_BUTTON_LEFT)) {
                    player.armors.Shoot(fishoder_entitys, shadowner_entitys, spikader_entitys, platforms_map, window);
                    cooldown = Global::ArmorData::cooldown;
                }
            }
        } else {
            if (!Global::ArmorData::Particles::fire) {
                float dur = 0.5;
                Camera::shake(dt, 40, 4, dur);
            }
            cooldown -= dt;
        }
    }
}

void ArcadeScene::Render(float dt, SDL_Event event, SDL_Window* window, SDL_Renderer *render, SDL_FPoint cam) {

    bool fisheated = player.fisheated;

    for (Platform &platforms : platforms_map) platforms.Draw(render, cam);
    for (Collectoon &collectoons : collectoon_map) collectoons.Draw(render, cam);
    for (Shadowner &shad : shadowner_entitys) shad.Draw(render, cam);
    for (Spikader &spiky : spikader_entitys) spiky.Draw(render, cam);
    for (Fishoder &fish : fishoder_entitys) fish.Draw(render, cam);
    for (Water &wat : water_map) wat.Draw(render, cam);
        

    UI::Renderize(dt, event, window, render, player.points, player.lives, &player);

    if (!fisheated) {
        player.func.Draw(render, cam);
    }
}