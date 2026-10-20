#include "player.h"
#include "../../include/SDL2/SDL_events.h"
#include "../../include/SDL2/SDL_gamecontroller.h"
#include "../../include/SDL2/SDL_mouse.h"
#include "../../include/SDL2/SDL_rect.h"
#include "../../include/SDL2/SDL_render.h"
#include "../../include/SDL2/SDL_scancode.h"
#include "../../include/SDL2/SDL_video.h"
#include "../../plugins/betterInput/betterInput.hpp"
#include "../../assets/download/assets.h"
#include "../UI/UI.hpp"
#include <cmath>

SDL_Texture* Player::sprite = nullptr;
int Player::currentFrame = 0;
int Player::jumpLeft = 0;
float Player::Current_World_Speed = 0.0f;
float Player::Apply_World_Speed = 150.0f;
float Player::gravity = 180.0f;
SDL_FPoint Player::position = {0.0f, 0.0f};
float Player::Vel_Y = 0.0f;
bool Player::stop = false;
bool Player::canStop = false;
bool Player::isOnFloor = false;
float Player::points = 0.0f;
float Player::multiplier = 1.0f;
bool Player::fisheated = false;
float Player::lives = 100.0f;
float Player::CooldownDamage = 5.0f;
bool Player::wasAttacked = false;
bool Player::Dead = false;
CurrentAction Player::currentAction = CurrentAction::Normal;

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
        case CurrentAnim::Damage:
            return Assets::PlayerAnim::damage;
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
                    Apply_World_Speed = 150;
                    jumpLeft = 2;
                    canStop = true;
                    inTransporter = false;
                    WhatPlatformIs = PlatformType::Normal;


                } else if (platmap.sprite == Assets::Platforms[1]) {
                    Vel_Y = 0.f;   
                    isOnFloor = true;
                    canStop = false;
                    inTransporter = false;
                    jumpLeft = 0;
                    WhatPlatformIs = PlatformType::Oil;

                } else if (platmap.sprite == Assets::Platforms[2]) {
                    Vel_Y = 0.f;   
                    isOnFloor = true;
                    Apply_World_Speed = 60;
                    jumpLeft = 1;
                    inTransporter = false;
                    WhatPlatformIs = PlatformType::Honey;

                } else if (platmap.sprite == Assets::Platforms[3]) {
                    Vel_Y = 0.f;   
                    isOnFloor = true;
                    Apply_World_Speed += 200 * dt;
                    jumpLeft = 0;
                    canStop = false;
                    inTransporter = false;
                    WhatPlatformIs = PlatformType::Ice;

                } else if (platmap.sprite == Assets::Platforms[4]) {
                    Vel_Y = 0.f;   
                    isOnFloor = true;
                    Apply_World_Speed = 150;
                    jumpLeft = 2;
                    canStop = true;
                    inTransporter = false;
                    if (CooldownDamage <= 0) {
                        lives -= 5;
                        UI::opacityflash = 255;
                        UI::negativeflash = 0;
                        wasAttacked = true;
                        CooldownDamage = 1.5;
                    }
                    WhatPlatformIs = PlatformType::Spikader;

                } else if (platmap.sprite == Assets::Platforms[5]) {
                    Vel_Y = -350.f;   
                    isOnFloor = false;
                    canStop = true;
                    jumpLeft = 2;
                    inTransporter = false;
                    WhatPlatformIs = PlatformType::Trampoder;

                } else if (platmap.sprite == Assets::Platforms[6]) {
                    Vel_Y = 0.f;   
                    isOnFloor = true;
                    canStop = true;
                    jumpLeft = 2;
                    inTransporter = true;
                    WhatPlatformIs = PlatformType::TranspRight;

                    if (stop) {
                        Apply_World_Speed += (platmap.velocity * 12) * dt;
                    } else {
                        Apply_World_Speed += (platmap.velocity * 14) * dt;
                    }

                } else if (platmap.sprite == Assets::Platforms[7]) {
                    Vel_Y = 0.f;   
                    isOnFloor = true;
                    canStop = true;
                    jumpLeft = 2;
                    inTransporter = true;
                    WhatPlatformIs = PlatformType::TranspLeft;

                    if (!stop) {
                        Current_World_Speed = (36.f - platmap.velocity) * 2.5;
                    } else {
                        Current_World_Speed = -platmap.velocity * 10;
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

void Player::CheckCollideEntitys(float dt, std::vector<Fishoder> &fish, std::vector<Shadowner> &shad, std::vector<Spikader> &spik) {
    for (Fishoder &fishoder : fish) {
        if (SDL_HasIntersectionF(&collide, &fishoder.collide) && fishoder.active) {
            fishdur = 7;
            UI::opacityflash = 255;
            UI::negativeflash = 0;
            wasAttacked = true;
            fisheated = true;
        }
    }

    for (Shadowner &shadowner : shad) {
        if (SDL_HasIntersectionF(&collide, &shadowner.collide) && shadowner.attack && shadowner.active) {
            if (CooldownDamage <= 0) {
                lives -= 3;
                CooldownDamage = 1.5;
                UI::opacityflash = 255;
                UI::negativeflash = 0;
                wasAttacked = true;
                shadowner.attack = false;
            }
        }
    }

    for (Spikader spikader: spik) {
        if (SDL_HasIntersectionF(&collide, &spikader.collide) && spikader.active) {
            if (CooldownDamage <= 0) {
                lives -= 4;
                UI::opacityflash = 255;
                UI::negativeflash = 0;
                wasAttacked = true;
                CooldownDamage = 1.5;
            }
        }
    }
}

void Player::Update(float dt, SDL_Window* window, SDL_Event event, bool isMoving) {
    
    collide.x = position.x + 70;
    collide.y = position.y + 72;

    if (WhatPlatformIs == PlatformType::TranspLeft && !isOnFloor) {
        Current_World_Speed = 50;
    }   
    
    if (fisheated) {
        fishdur -= dt;

        if (fishdur <= 0) {
            fisheated = false;
        }
    }

    int widthsprite;

    SDL_QueryTexture(sprite, NULL, NULL, &widthsprite, NULL);

    timeleftdt += dt;
    currentFrame = (int)(timeleftdt * 12) % (widthsprite / 92);

    Current_World_Speed += (Apply_World_Speed - Current_World_Speed) * (1.0f - exp(-dt * (150.0f / (1.0f + fabsf(Current_World_Speed)))));

    if (lives < 0) {
        lives = 0;
        Dead = true;
    }

    if (!wasAttacked && !Dead) {
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
    } else {
        sprite = loadTexture(CurrentAnim::Damage);
    }

    if (!fisheated) {
        if (!wasAttacked) {
            if (stop) {
                currentAction = CurrentAction::Stoped;
            } else {
                currentAction = CurrentAction::Normal;
            }
        } else {
            currentAction = CurrentAction::Damage;
        }

        Functions::ActionsAndStuffs(dt, window, event, isMoving);
    } else {
        currentAction = CurrentAction::Fisheated;
        stop = false;
        canStop = false;
        points -= 50 * dt;
    }
    
    if (lastsprite != sprite) {
        currentFrame = 0;
        timeleftdt = 0;
        lastsprite = sprite;
    }

}

void Player::Functions::ActionsAndStuffs(float dt, SDL_Window* window, SDL_Event event, bool isMoving) {
    if (isMoving) {
        points += (Current_World_Speed * multiplier) * dt;
    }

    if (CooldownDamage > 0) {
        CooldownDamage -= dt;
    } else {
        wasAttacked = false;
    }

    if (!isOnFloor) {
        Vel_Y += gravity * dt;
        position.y += Vel_Y * dt;
    }
    
    if (InputMapping(window, event, TypeMapping::Jump) && jumpLeft > 0) {
        Vel_Y = -180;
        isOnFloor = false;
        jumpLeft--;
    }

    if (canStop) {
        stop = InputMapping(window, event, TypeMapping::Stop);
    } else {
        stop = false;
    }
}

void Player::Functions::Draw(SDL_Renderer *render, SDL_FPoint campos) {

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

    SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
    SDL_SetTextureColorMod(sprite, (Uint8)UI::negativeflash, (Uint8)UI::negativeflash, (Uint8)UI::negativeflash);

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