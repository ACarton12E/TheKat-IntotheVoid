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
#include "../../Global.h"
#include "../UI/UI.h"
#include "../../plugins/camera/camera.h"
#include <cmath>

SDL_Texture* Player::sprite = nullptr;
int Player::currentFrame = 0;
int Player::jumpLeft = 0;
float Player::Current_World_Speed = 0.0f;
float Player::Apply_World_Speed = 180.0f;
float Player::gravity = 280.0f;
float Player::rotation = 0.0f;
SDL_FPoint Player::position = {0.0f, 0.0f};
SDL_FPoint Player::SizeSprite = {90, 102};
float Player::Vel_Y = 0.0f;
bool Player::stop = false;
bool Player::canStop = false;
bool Player::isOnFloor = false;
bool Player::inWater = false;
bool Player::AskeMode = false;
float Player::points = 0.0f;
float Player::multiplier = 1.0f;
bool Player::fisheated = false;
bool Player::flying = false;
bool Player::iCanFlyBTW = false;
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

        case TypeMapping::Fly:
            if (BetterInput::Mouse::onSwipe(event, SDL_BUTTON_LEFT, swipeDir::Right)) return true;

            if (BetterInput::Keyboard::onJustPressed(event, SDL_SCANCODE_X)) return true;

            if (BetterInput::Gamepad::onJustPressed(event, 0, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) return true;

        break;
    }

    return false;
}

SDL_Texture* Player::loadTexture(CurrentAnim anim) {
    if (AskeMode) {
        switch (anim) {
            case CurrentAnim::Idle:
                return Assets::PlayerAnim::ASKE::idle;
            break;

            case CurrentAnim::Walk:
                return Assets::PlayerAnim::ASKE::walk;
            break;

            case CurrentAnim::Jump:
                return Assets::PlayerAnim::ASKE::jump;
            break;

            case CurrentAnim::Fall:
                return Assets::PlayerAnim::ASKE::fall;
            break;

            case CurrentAnim::Swim:
                return Assets::PlayerAnim::ASKE::swim;
            break;
            default: return Assets::PlayerAnim::ASKE::idle;
        }
    } else {
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

            case CurrentAnim::Flying:
                return Assets::PlayerAnim::flying;
                break;

            case CurrentAnim::BadFlying:
                return Assets::PlayerAnim::badFlying;
                break;

            case CurrentAnim::SplashFloor:
                return Assets::PlayerAnim::splashFloor;
                break;

            case CurrentAnim::Damage:
                return Assets::PlayerAnim::damage;
                break;

            default: return Assets::PlayerAnim::idle;
        }
    }
}

void Player::Create() {
    position.x = 0; 
    position.y = 0;

    currentFrame = 0;
    currentAnim = CurrentAnim::Idle;
    Current_World_Speed = 200;
    stop = false;
    Vel_Y = 0.f;

    sprite = loadTexture(currentAnim);

    if (Player::ArmorHand::particle == nullptr) {
        Player::ArmorHand::particle = new ParticleSys(Global::ArmorData::Particles::count);
    }

}

void Player::CheckCollide(float dt, 
    std::vector<Platform> &platform,
    std::vector<Collectoon> &collectoon,
    std::vector<Water> &water
    ) 
    {

    isOnFloor = false;
    for (Platform &platmap : platform) {
        if (SDL_HasIntersectionF(&collide, &platmap.collide) && !inWater) {
            if (Vel_Y > 0.02f && ((position.y + 192) <= (platmap.collide.y + 25))) {
                position.y = platmap.position.y - 192;                      
                isOnFloor = true;

                if (flying && iCanFlyBTW) {
                    lives -= 10;
                    CooldownDamage = 2.0f;
                    wasAttacked = true;
                    stop = true;
                    UI::negativeflash = 0.0f;
                    UI::opacityflash = 255.0f;

                    float dur = 0.5f;
                    Camera::shake(dt, 35.0f, 8.0f, dur);
                }

                if (platmap.sprite != Assets::Platforms[5]) {
                    flying = false;
                }
                
                if (platmap.sprite == Assets::Platforms[0]) {
                    Vel_Y = 0.f;  
                    Apply_World_Speed = 200;
                    jumpLeft = 2;
                    canStop = true;
                    isOnFloor = true;
                    inTransporter = false;
                    WhatPlatformIs = PlatformType::Normal;


                } else if (platmap.sprite == Assets::Platforms[1]) {
                    Vel_Y = 0.f;   
                    canStop = false;
                    inTransporter = false;
                    jumpLeft = 0;
                    isOnFloor = true;
                    WhatPlatformIs = PlatformType::Oil;

                } else if (platmap.sprite == Assets::Platforms[2]) {
                    Vel_Y = 0.f;   
                    Apply_World_Speed = 100;
                    jumpLeft = 1;
                    isOnFloor = true;
                    inTransporter = false;
                    WhatPlatformIs = PlatformType::Honey;

                } else if (platmap.sprite == Assets::Platforms[3]) {
                    Vel_Y = 0.f;   
                    isOnFloor = true;
                    Apply_World_Speed += 400 * dt;
                    jumpLeft = 0;
                    canStop = false;
                    inTransporter = false;
                    WhatPlatformIs = PlatformType::Ice;

                } else if (platmap.sprite == Assets::Platforms[4]) {
                    Vel_Y = 0.f;   
                    Apply_World_Speed = 200;
                    jumpLeft = 2;
                    canStop = true;
                    isOnFloor = true;
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
                    Vel_Y = -600.f;   
                    isOnFloor = false;
                    canStop = true;
                    jumpLeft = 2;
                    inTransporter = false;
                    WhatPlatformIs = PlatformType::Trampoder;

                } else if (platmap.sprite == Assets::Platforms[6]) {
                    Vel_Y = 0.f;   
                    canStop = true;
                    jumpLeft = 2;
                    isOnFloor = true;
                    inTransporter = true;
                    WhatPlatformIs = PlatformType::TranspRight;

                    if (stop) {
                        Apply_World_Speed += (platmap.velocity * 18) * dt;
                    } else {
                        Apply_World_Speed += (platmap.velocity * 28) * dt;
                    }

                } else if (platmap.sprite == Assets::Platforms[7]) {
                    Vel_Y = 0.f;   
                    isOnFloor = true;
                    canStop = true;
                    jumpLeft = 2;
                    inTransporter = true;
                    WhatPlatformIs = PlatformType::TranspLeft;

                    if (!stop) {
                        Current_World_Speed = (64.f - platmap.velocity) * 3;
                        Apply_World_Speed = (64.f - platmap.velocity) * 3;
                    } else {
                        Current_World_Speed = -platmap.velocity * 20;
                        Apply_World_Speed = (64.f - platmap.velocity) * 3;
                    }

                }
            }
        }
    }

    for (Collectoon &collmap : collectoon) {
        if (SDL_HasIntersectionF(&collide, &collmap.collide) && !collmap.Katched) {
            switch (collmap.foodType) {
                case FoodType::Ketchup: {
                    points += 500;
                    multiplierdur = 6;
                    multiplier += (multiplier == 1 ? 1 : 2);
                    lives += 5;
                } break;
                case FoodType::Cookie: {
                    points += 100;
                } break;
                case FoodType::ToddyCake: {
                    points += 250;
                } break;
                case FoodType::PotatoMcMaco: {
                    points += 200;
                } break;
                case FoodType::Hamburgo: {
                    points += 400;
                } break;
                case FoodType::UghFish: {
                    points -= 200;
                    multiplier -= 1;
                } break;
                case FoodType::Brocolee: {
                    points += 450;
                } break;
                case FoodType::ChocoMcMaco: {
                    points += 128;
                } break;
                case FoodType::HawaianPizza: {
                    points += 560;
                } break;
                case FoodType::BismolOtpep: {
                    points += 680;
                    lives += 3;
                } break;
                case FoodType::Mayo: {
                    points += 200;
                    multiplierdur = 6;
                    multiplier += (multiplier == 1 ? 3 : 4);
                    lives += 5;
                } break;
                case FoodType::Guacamole: {
                    points += 200;
                    multiplierdur = 6;
                    multiplier += (multiplier == 1 ? 5 : 6);
                    lives += 10;
                } break;
                case FoodType::Kerozink: {
                    points += 200;
                    multiplierdur = 6;
                    multiplier += (multiplier == 1 ? 7 : 8);
                    lives += 15;
                } break;
            }

            Mix_VolumeChunk(Assets::Sounds::Katched, 40);
            Mix_PlayChannel(-1, Assets::Sounds::Katched, 0);

            collmap.Katched = true;
        }
    }

    inWater = false;

    for (Water &wat : water) {
        if (SDL_HasIntersectionF(&collide, &wat.collide)) {
            inWater = true;
        }
    }
}

void Player::CheckCollideEntitys(float dt, std::vector<Fishoder> &fish, std::vector<Shadowner> &shad, std::vector<Spikader> &spik) {
    for (Fishoder &fishoder : fish) {
        if (SDL_HasIntersectionF(&collide, &fishoder.collide) && (fishoder.active && !fishoder.dead)) {
            fishdur = 7;
            Mix_PlayChannel(-1, Assets::Sounds::Damage, 0);
            UI::opacityflash = 255;
            UI::negativeflash = 0;
            multiplier = 0;
            wasAttacked = true;
            fisheated = true;
        }
    }

    for (Shadowner &shadowner : shad) {
        if (SDL_HasIntersectionF(&collide, &shadowner.collide) && shadowner.attack && shadowner.active) {
            if (CooldownDamage <= 0) {
                lives -= 3;
                Mix_PlayChannel(-1, Assets::Sounds::Damage, 0);
                CooldownDamage = 1.5;
                UI::opacityflash = 255;
                UI::negativeflash = 0;
                multiplier -= 25;
                wasAttacked = true;
                shadowner.attack = false;
            }
        }
    }

    for (Spikader &spikader: spik) {
        if (SDL_HasIntersectionF(&collide, &spikader.collide) && spikader.active) {
            if (CooldownDamage <= 0) {
                lives -= 4;
                Mix_PlayChannel(-1, Assets::Sounds::Damage, 0);
                UI::opacityflash = 255;
                UI::negativeflash = 0;
                multiplier -= 10;
                wasAttacked = true;
                CooldownDamage = 1.5;
            }
        }
    }
}

void Player::Update(float dt, SDL_Window* window, SDL_Event event, bool isMoving, SDL_FPoint campos) {

    if (lives >= 100.0f) lives = 99.99f;
    if (multiplier <= 0) multiplier = 1; else { multiplierdur -= dt; }

    if (multiplierdur <= 0) {
        multiplier = 1;
    }
    


    collide.x = position.x + (SizeSprite.x - 22);
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

    if (sprite == Assets::PlayerAnim::walk) {
        currentFrame = (int)(timeleftdt * (Current_World_Speed / 24)) % (widthsprite / (int)SizeSprite.x);
    } else {
        currentFrame = (int)(timeleftdt * 12) % (widthsprite / (int)SizeSprite.x);
    }

    if (isOnFloor || inWater) {
        Current_World_Speed += (Apply_World_Speed - Current_World_Speed) * (1.0f - exp(-dt * (150.0f / (1.0f + fabsf(Current_World_Speed)))));
    }

    if (lives < 0) {
        lives = 0;
        Dead = true;
    }


    if ((wasAttacked || Dead) && !AskeMode && !iCanFlyBTW) {
        sprite = loadTexture(CurrentAnim::Damage);
    }

    else {
        if (!isOnFloor) {
            if (!inWater) {
                if (!flying) {
                    if (fabsf(Vel_Y) > 20.0f) rotation += (0 - rotation) * (dt * 20);

                    if (Vel_Y > 20.0f) {
                        sprite = loadTexture(CurrentAnim::Fall);
                    } else if (Vel_Y < -20.0f) {
                        sprite = loadTexture(CurrentAnim::Jump);
                    }
                } else {
                    if (!iCanFlyBTW) {
                        sprite = loadTexture(CurrentAnim::Flying);
                    } else {
                        if (fabsf(Vel_Y) > 20.0f) {
                            sprite = loadTexture(CurrentAnim::BadFlying);
                            rotation += 320 * dt;
                        }
                    }
                }
            } else {
                sprite = loadTexture(CurrentAnim::Swim);
            }
        } else {
            if (!iCanFlyBTW && !flying) {
                if (stop) {
                    sprite = loadTexture(CurrentAnim::Idle);
                } else {
                    sprite = loadTexture(CurrentAnim::Walk);
                }
            } else if (iCanFlyBTW) {
                rotation = 0;
                sprite = loadTexture(CurrentAnim::SplashFloor);
            }
        }
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

        Functions::ActionsAndStuffs(dt, window, event, isMoving, campos);
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

void Player::Functions::ActionsAndStuffs(float dt, SDL_Window* window, SDL_Event event, bool isMoving, SDL_FPoint campos) {
    if (isMoving) {
        points += ((Current_World_Speed / 6) * multiplier) * dt;
    }

    if (CooldownDamage > 0) {
        CooldownDamage -= dt;
    } else {
        wasAttacked = false;
    }

    if (!isOnFloor) {
        if (flying && !iCanFlyBTW) {
            rotation += ((atan2f(Vel_Y, Current_World_Speed) * (180.0f / M_PI)) - rotation) * (dt * 20);

            if (rotation >= 40) {
                iCanFlyBTW = true;
            }
        }
    }



    if (AskeMode) {
        SizeSprite = {150, 180};
        ArmorHand::position = position;
        ArmorHand::Update(dt, window, event, campos);
    } else {
        SizeSprite = {92, 102};
    }

    if (!inWater) {
        if (!isOnFloor && !inWater) {
            Vel_Y += gravity * dt;
            position.y += Vel_Y * dt;
        }

        if (InputMapping(window, event, TypeMapping::Jump) && jumpLeft > 0) {
            Vel_Y = -280;
            iCanFlyBTW = false;
            isOnFloor = false;
            jumpLeft--;
        }

        if (canStop && !iCanFlyBTW) {
            stop = InputMapping(window, event, TypeMapping::Stop);
        } else if (!canStop) {
            stop = false;
        }

        if (InputMapping(window, event, TypeMapping::Fly)) {
            flying = true;
        }

    } else {
        WaterOrSuper(dt, window, event, campos);
    }

}

void Player::Functions::WaterOrSuper(float dt, SDL_Window* window, SDL_Event event, SDL_FPoint campos) {
    int mousex, mousey;
    SDL_GetMouseState(&mousex, &mousey);

    stop = false;
    isOnFloor = false;

    float dx = (float)mousex - (position.x - campos.x);
    float dy = (float)mousey - (position.y - campos.y);
    jumpLeft = 2;

    float atan = atan2(dy, dx);

    rotation += (atan * (180.0f / M_PI) - rotation) * (dt * 20);

    Apply_World_Speed = cos(atan) * 450.0f;
    Vel_Y = sin(atan) * 560.0f;

    position.y += Vel_Y * dt;

}

void Player::Functions::Draw(SDL_Renderer *render, SDL_FPoint campos) {

    SDL_FRect dest = {
        position.x - campos.x,
        (position.y - campos.y) - (AskeMode ? (SizeSprite.y - 20) : 0),
        SizeSprite.x * 2,
        SizeSprite.y * 2
    };

    SDL_Rect src = {
        (int)SizeSprite.x * currentFrame,
        0,
        (int)SizeSprite.x,
        (int)SizeSprite.y
    };

    SDL_FPoint point = {SizeSprite.x, SizeSprite.y};

    SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
    SDL_SetTextureColorMod(sprite, (Uint8)UI::negativeflash, (Uint8)UI::negativeflash, (Uint8)UI::negativeflash);

    SDL_RenderCopyExF(
        render, 
        sprite, 
        &src, 
        &dest, 
        rotation,
        &point, 
        SDL_RendererFlip::SDL_FLIP_NONE
    );

    if (AskeMode) {
        ArmorHand::Render(render, campos);
    }
}

#pragma Hand Armor

float Player::ArmorHand::rotation = 0.0f;
SDL_FPoint Player::ArmorHand::position = {0.0f, 0.0f};
ParticleSys* Player::ArmorHand::particle = nullptr;
bool Player::ArmorHand::isShootingFire = false;

void Player::ArmorHand::Update(
    float dt, SDL_Window* window,
    SDL_Event event,
    SDL_FPoint campos
) {

    int mousex, mousey;

    SDL_GetMouseState(&mousex, &mousey);

    collideS = {(float)mousex + campos.x, (float)mousey + campos.y, Global::ArmorData::size, Global::ArmorData::size};
    float weaponPivotX = (position.x + 75.0f + 36.0f) - campos.x;
    float weaponPivotY = (position.y - 120.0f + 118.0f) - campos.y;

    float dx = (float)mousex - weaponPivotX;
    float dy = (float)mousey - weaponPivotY;

    float atan = atan2(dy, dx);

    rotation += (atan * (180.0f / M_PI) - rotation) * (dt * 20);

    if (Player::ArmorHand::particle != nullptr) {
        Player::ArmorHand::particle->update();
    }

    if (Global::CurrentArmor == 5) {
        if (BetterInput::Mouse::onPressed(SDL_BUTTON_LEFT)) {

            for (int i = 0; i < 3; i++) {

                float armWorldX = position.x + 75.0f;
                float armWorldY = position.y - 120.0f;

                float pivotWorldX = armWorldX + 36.0f;
                float pivotWorldY = armWorldY + 118.0f;

                float lengthX = 340.0f;
                float lengthY = 13.0f;

                float finalX = pivotWorldX + (lengthX * cos(atan) - lengthY * sin(atan));
                float finalY = pivotWorldY + (lengthX * sin(atan) + lengthY * cos(atan));

                float disper = ((rand() % 100) - 50) / 300.0f;
                float angle = atan + disper;

                float force = 4.5f + ((rand() % 100) / 50.0f);
                float vx = cos(angle) * force;
                float vy = sin(angle) * force;

                int life = 170 + (rand() % 110);

                SDL_Color color = {255, 255, 255, 0};

                if (Player::ArmorHand::particle != nullptr) {
                    Player::ArmorHand::particle->emit(finalX, finalY, vx, vy, life, 0, Global::ArmorData::Particles::assets, true, color);

                }
            }
        }
    }

    if (Global::ArmorData::Particles::fire) {
        if (!isShootingFire && Mix_Playing(2)) {
            Mix_HaltChannel(2);
        }

        isShootingFire = false;
    }
}

void Player::ArmorHand::Shoot(
    std::vector<Fishoder> &fishs,
    std::vector<Shadowner> &shads,
    std::vector<Spikader> &spiks,
    std::vector<Platform> &plats,
    SDL_Window* window
) {
    if (!Global::ArmorData::Particles::fire) {

        Mix_PlayChannel(-1, Assets::PlayerAnim::ASKE::sound, 0);
        Mix_VolumeChunk(Assets::PlayerAnim::ASKE::sound, 25);

        UI::negativeflash = 50;
        UI::opacityflash = 50;



        for ( Fishoder &fish : fishs ) {
            if (SDL_HasIntersectionF(&collideS, &fish.collide) && (!fish.dead && fish.active)) {
                Mix_PlayChannel(-1, Assets::Sounds::DamageEnemie, 0);
                fish.dead = true;
            }
        }
        for ( Shadowner &shad : shads ) {
            if (SDL_HasIntersectionF(&collideS, &shad.collide) && (!shad.dead && shad.active)) {
                Mix_PlayChannel(-1, Assets::Sounds::DamageEnemie, 0);
                shad.dead = true;
            }
        }
        for ( Spikader &spik : spiks ) {
            if (SDL_HasIntersectionF(&collideS, &spik.collide)) {
                Mix_PlayChannel(-1, Assets::Sounds::DamageEnemie, 0);
                spik.position.x = 200;
            }
        }
        for ( Platform &plat : plats ) {
            if ((SDL_HasIntersectionF(&collideS, &plat.collide) && plat.sprite == Assets::Platforms[1]) && !plat.explote) {
                Mix_VolumeChunk(Assets::Sounds::Explotion, 25);
                Mix_PlayChannel(-1, Assets::Sounds::Explotion, 0);
                plat.Explote(fishs, shads, spiks, plats);
                plat.explote = true;
            }
        }

    } else {

        isShootingFire = true;

        if (!Mix_Playing(2)) {
            Mix_PlayChannel(2, Assets::PlayerAnim::ASKE::sound, 0);
            Mix_VolumeChunk(Assets::PlayerAnim::ASKE::sound, 15);
        }

        for (int i = 0; i < 3; i++) {
            if (Player::ArmorHand::particle != nullptr) {
                Player::ArmorHand::particle->damage(fishs, shads, spiks, plats);
            }
        }
    }
}

void Player::ArmorHand::Render(SDL_Renderer* render, SDL_FPoint campos) {

    int mousex, mousey;
    SDL_GetMouseState(&mousex, &mousey);
    SDL_FRect sh = {(float)mousex, (float)mousey, 32, 32};

    SDL_Rect src = {0, 0, 240, 120};
    SDL_FRect dest = {(position.x + 75) - campos.x, (position.y - 120) - campos.y, 240 * 2, 128 * 2};

    SDL_FPoint point = {36, 118};

    SDL_RenderCopyF(render, Assets::PlayerAnim::ASKE::sight, NULL, &sh);

    if (Player::ArmorHand::particle != nullptr) {
        Player::ArmorHand::particle->render(render, campos);
    }

    SDL_RenderCopyExF(
        render,
        Assets::PlayerAnim::ASKE::gun,
        &src,
        &dest,
        rotation,
        &point,
        SDL_FLIP_NONE
    );
}