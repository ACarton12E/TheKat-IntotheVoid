#include "player.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_gamecontroller.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>
#include "../../plugins/betterInput/betterInput.hpp"
#include "../../assets/download/assets.h"

bool Player::InputMapping(SDL_Window* window, const SDL_Event &event, TypeMapping type) {

    SDL_Point mousepos;
    int w;
    SDL_GetWindowSize(window, &w, NULL);

    switch (type) {
        case TypeMapping::Jump: 
            if (BetterInput::Keyboard::onJustPressed(event, SDL_SCANCODE_SPACE)) return true;

            if (BetterInput::Gamepad::onJustPressed(event, 0, SDL_CONTROLLER_BUTTON_A)) return true;

            if (BetterInput::Mouse::onJustPressedwithPosition(event, SDL_BUTTON_LEFT, mousepos) 
            && mousepos.x >= w / 2) return true;

        break;

        case TypeMapping::Stop: 
            if (BetterInput::Keyboard::onPressed(SDL_SCANCODE_LSHIFT)) return true;

            if (BetterInput::Gamepad::onPressed(0, SDL_CONTROLLER_BUTTON_X)) return true;

            if (BetterInput::Mouse::onPressedwithPosition(SDL_BUTTON_LEFT, mousepos) 
            && mousepos.x < w / 2) return true;

        break;
    }

    return false;
}

SDL_Texture* Player::loadTexture(CurrentAnim anim) {
    switch (anim) {
        case CurrentAnim::Idle: 
            return Assets::PlayerAnim::idle;
        break;
        
        case CurrentAnim::Walk: 
            return Assets::PlayerAnim::walk;
        break;

        case CurrentAnim::Jump: 
            return Assets::PlayerAnim::jump;
        break;

        case CurrentAnim::Fall: 
            return Assets::PlayerAnim::fall;
        break;

        case CurrentAnim::Swim: 
            return Assets::PlayerAnim::swim;
        break;
        default: return Assets::PlayerAnim::idle;
    }
}

void Player::Create() {
    position.x = 0; 
    position.y = 0;

    currentFrame = 0;
    currentAnim = CurrentAnim::Idle;
    Current_World_Speed = 150;
    stop = false;
    Vel_Y = 0.f;

    sprite = loadTexture(currentAnim);
}

void Player::CheckCollide(float dt, 
    std::vector<Platform> &platform,
    std::vector<Collectoon> &collectoon
    ) 
    {

    isOnFloor = false;
    for (Platform &platmap : platform) {
        if (SDL_HasIntersectionF(&collide, &platmap.Collide)) {
            if (Vel_Y > 0.02f && ((position.y + 192) <= (platmap.Collide.y + 25))) {      
                position.y = platmap.position.y - 192;                      
                isOnFloor = true;
                
                if (platmap.sprite == Assets::Platforms[0]) {
                    Vel_Y = 0.f;  
                    isOnFloor = true; 
                    Current_World_Speed = 150;
                    canStop = true;
                    inTransporter = false;
                    WhatPlatformIs = PlatformType::Normal;


                } else if (platmap.sprite == Assets::Platforms[1]) {
                    Vel_Y = 0.f;   
                    isOnFloor = true;
                    canStop = false;
                    inTransporter = false;
                    WhatPlatformIs = PlatformType::Oil;

                } else if (platmap.sprite == Assets::Platforms[2]) {
                    Vel_Y = 0.f;   
                    isOnFloor = true;
                    Current_World_Speed = 60;
                    inTransporter = false;
                    WhatPlatformIs = PlatformType::Honey;

                } else if (platmap.sprite == Assets::Platforms[3]) {
                    Vel_Y = 0.f;   
                    isOnFloor = true;
                    Current_World_Speed += 200 * dt;
                    canStop = false;
                    inTransporter = false;
                    WhatPlatformIs = PlatformType::Ice;

                } else if (platmap.sprite == Assets::Platforms[4]) {
                    Vel_Y = 0.f;   
                    isOnFloor = true;
                    Current_World_Speed = 150;
                    canStop = true;
                    inTransporter = false;
                    WhatPlatformIs = PlatformType::Spikader;

                } else if (platmap.sprite == Assets::Platforms[5]) {
                    Vel_Y = -200.f;   
                    isOnFloor = false;
                    canStop = true;
                    inTransporter = false;
                    WhatPlatformIs = PlatformType::Trampoder;

                } else if (platmap.sprite == Assets::Platforms[6]) {
                    Vel_Y = 0.f;   
                    isOnFloor = true;
                    canStop = true;
                    inTransporter = true;
                    WhatPlatformIs = PlatformType::TranspRight;

                    if (stop) {
                        Current_World_Speed += 180 * dt;
                    } else {
                        Current_World_Speed += 250 * dt;
                    }

                } else if (platmap.sprite == Assets::Platforms[7]) {
                    Vel_Y = 0.f;   
                    isOnFloor = true;
                    canStop = true;
                    inTransporter = true;
                    WhatPlatformIs = PlatformType::TranspLeft;

                    if (!stop) {
                        Current_World_Speed = 50;
                    } else {
                        Current_World_Speed = -100;
                    }

                }
            }
        }
    }

    for (Collectoon &collmap : collectoon) {
        if (SDL_HasIntersectionF(&collide, &collmap.collide) && !collmap.Katched) {
            collmap.Katched = true;
        }
    }
}

void Player::Update(float dt, SDL_Window* window, SDL_Event event) {

    if (!isOnFloor) {
        Vel_Y += gravity * dt;
        position.y += Vel_Y * dt;
    }

    
    collide.x = position.x + 70;
    collide.y = position.y + 72;

    if (WhatPlatformIs == PlatformType::TranspLeft && !isOnFloor) {
        Current_World_Speed = 150;
    }   

    if (InputMapping(window, event, TypeMapping::Jump)) {
        Vel_Y = -180;
        isOnFloor = false;
    }

    if (canStop) {
        stop = InputMapping(window, event, TypeMapping::Stop);
    } else {
        stop = false;
    }
    

    int widthsprite;

    SDL_QueryTexture(sprite, NULL, NULL, &widthsprite, NULL);

    timeleftdt += dt;
    currentFrame = (int)(timeleftdt * 12) % (widthsprite / 92);


    if (!isOnFloor) {
        if (Vel_Y > 20.0) {
            sprite = loadTexture(CurrentAnim::Fall);
        } else if (Vel_Y < -20.0) {
            sprite = loadTexture(CurrentAnim::Jump);
        }
    } else {
        if (stop) {
            sprite = loadTexture(CurrentAnim::Idle);
        } else {
            sprite = loadTexture(CurrentAnim::Walk);
        }
    }
    
    if (lastsprite != sprite) {
        currentFrame = 0;
        timeleftdt = 0;
        lastsprite = sprite;
    }

}

void Player::Draw(SDL_Renderer *render, SDL_FPoint campos) {

    SDL_FRect dest = {
        position.x - campos.x,
        position.y - campos.y,
        92 * 2,
        102 * 2
    };

    SDL_Rect src = {
        92 * currentFrame,
        0,
        92 ,
        102
    };

    SDL_FPoint point = {0, 0};

    SDL_RenderCopyExF(
        render, 
        sprite, 
        &src, 
        &dest, 
        0, 
        &point, 
        SDL_RendererFlip::SDL_FLIP_NONE
    );
}