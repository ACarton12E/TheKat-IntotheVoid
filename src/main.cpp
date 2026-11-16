#include "include/SDL2/SDL_events.h"
#include "include/SDL2/SDL_gamecontroller.h"
#include "include/SDL2/SDL_mixer.h"
#include "include/SDL2/SDL_mouse.h"
#include "include/SDL2/SDL_rect.h"
#include "include/SDL2/SDL_render.h"
#include "include/SDL2/SDL_timer.h"
#include "include/SDL2/SDL_ttf.h"
#include "include/SDL2/SDL_video.h"
#include "include/SDL2/SDL.h"
#include <cstdlib>
#include <iostream>

#ifdef __WII__
#include <fat.h>
#include <wiikeyboard/keyboard.h>
#endif


#include "scenes/arcade/arcade.h"

#include "assets/download/assets.h"
#include "plugins/camera/camera.h"
#include "plugins/betterInit/betterInit.hpp"
#include "plugins/betterInput/betterInput.hpp"
#include "Global.h"
#include "code/UI/UI.h"

SCENES Global::CurrentScene = SCENES::MENU;

void Camera::shake(float dt, float freq, float amp, float& dur) {
    position.x -= lastOffset.x;
    position.y -= lastOffset.y;

    if (dur > 0.0f) {
        elapsedTime += dt;
        dur -= dt;

        lastOffset.x = cosf(elapsedTime * freq) * amp;
        lastOffset.y = sinf(elapsedTime * freq * 1.1f) * amp;

        position.x += lastOffset.x;
        position.y += lastOffset.y;
    } else {
        elapsedTime = 0.0f;
        lastOffset = {0.0f, 0.0f};
    }
}



int main(int argc, char **argv) {


    SDL_GameController* pad;
    SDL_Window* window;
    SDL_Renderer* render;

    ArcadeScene arcadescn;

    int result = BetterInit::loadSDLwithGamepad(
        { "The Kat - Clangs Into the Void!", 1280, 720, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, Assets::icon },
        { -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED },
        pad, 
        window, 
        render
    );

    if (result != 0) {
        return result;
    }


    if (TTF_Init() == -1) {
        SDL_Log("Oh, the Font! Uhhh %s", TTF_GetError());
    }

    Mix_Init(MIX_INIT_OGG);

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        SDL_Log("Oh, the Audio! Uhhh %s", Mix_GetError());
    }


    Assets::LoadAll(render);
    Assets::LoadCurrent(render, "assets/json/players/thekat.json");
    srand(time(NULL));

    
    Mix_PlayMusic(Assets::Musics::IntotheVoid, -1);
    
    UI::Preload(render);

    bool loopithing = true;
    SDL_Event event;


    bool moving = false;

    Camera cam;
    float xtest;

    cam.zoom = 1.5;

    double dt = 0.0;
    Uint32 last_time = SDL_GetTicks();
    int desplX = 0;

    SCENES LastScene = SCENES::ARCADE;

    SDL_FPoint playPos = {0, 0};
    float CamSpeed = 120;

    while (loopithing) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                loopithing = false;
            }
        }

        int w, h;

        SDL_GetWindowSize(window, &w, &h);

        if (BetterInput::Keyboard::onJustPressed(event, SDL_SCANCODE_KP_ENTER) && BetterInput::Gamepad::onJustPressed(event, 0, SDL_CONTROLLER_BUTTON_START)) {
            Global::CurrentScene = SCENES::ARCADE;
        } else if (BetterInput::Keyboard::onJustPressed(event, SDL_SCANCODE_ESCAPE) && BetterInput::Gamepad::onJustPressed(event, 0, SDL_CONTROLLER_BUTTON_BACK)) {
            Global::CurrentScene = SCENES::MENU;
        }

        if (LastScene != Global::CurrentScene) {
            if (Global::CurrentScene == SCENES::ARCADE) {
                arcadescn.generate();
            } else { 
                UI::Preload(render);
                CamSpeed = 120;
                playPos = {0, (float)-h * 2};
            }
            LastScene = Global::CurrentScene;
        }

        

        Uint32 current_time = SDL_GetTicks();
        dt = (current_time - last_time) / 1000.0; 
        last_time = current_time;

        //xtest += 20 * dt;

        
        

        SDL_SetRenderDrawColor(render, 0, 0, 0, 255);   
        SDL_RenderClear(render);

        if (Global::CurrentScene == SCENES::ARCADE) {
            arcadescn.Update(dt, event, window, render, playPos, CamSpeed, cam.position);
        }

        cam.position.x += (playPos.x - cam.position.x) * (dt * 5);
        cam.position.y += ((playPos.y - 250.0f) - cam.position.y) * (dt * 5);

        int texW = 0, texH = 0;
        SDL_QueryTexture(Assets::Background, NULL, NULL, &texW, &texH);

        if (!moving) {
            desplX += (80) * dt;
        } else {
            desplX += (((CamSpeed / 5) + 80) ) * dt;
            desplX += (((120.0 / 5) + 80) ) * dt;
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

        if (Global::CurrentScene == SCENES::ARCADE) {
            arcadescn.Render(dt, event, window, render, cam.position);

            Mix_VolumeMusic(86);
        } else if (Global::CurrentScene == SCENES::MENU) {
            Mix_VolumeMusic(MIX_MAX_VOLUME);
            SDL_Rect playsrc = {0, 0, 440, 74};
            SDL_FRect playdest = {-200 * 1.5, (float)h / 2, 440 * 1.5, 74 * 1.5};

            SDL_Point mousepos;


            if (BetterInput::Mouse::onJustPressedwithPosition(event, SDL_BUTTON_LEFT, mousepos)) {
                SDL_FPoint mousefpos = {(float)mousepos.x, (float)mousepos.y}; 
                if (SDL_PointInFRect(&mousefpos, &playdest)) {
                    Global::CurrentScene = SCENES::ARCADE;
                }
            }

            SDL_RenderCopyF(render, Assets::UI::Menu::Play, &playsrc, &playdest);

            SDL_Rect logosrc = {0, 0, 190, 143};
            SDL_FRect logodest = {(w / 2.0f) - 190.0f + 140.0f, (h / 2.0f) - 143.0f - 40.0f, 190.0f * 2, 143.0f * 2};
            SDL_RenderCopyF(
                render, 
                Assets::Logo, 
                &logosrc, 
                &logodest
            );

        }

        SDL_RenderPresent(render);
    }

    UI::Clean();

    TTF_CloseFont(Assets::UI::Fonts::eas_analog);
    TTF_CloseFont(Assets::UI::Fonts::monogram_ext);
    TTF_CloseFont(Assets::UI::Fonts::uniex_mono);
    TTF_Quit();

    Mix_CloseAudio();
    Mix_Quit();

    BetterInit::unloadSDLwithGamepad(render, window, pad);

    SDL_Quit();

    return 0;
}
