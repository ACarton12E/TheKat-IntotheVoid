#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_gamecontroller.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <stdlib.h>

class WindowConfig {
    public:
    const char* title = "Hello, World!";
    int w = 800;
    int h = 600;
    int x = SDL_WINDOWPOS_CENTERED;
    int y = SDL_WINDOWPOS_CENTERED;
    Uint32 flags = SDL_WINDOW_SHOWN;
};

class RenderConfig {
    public:
    int index = -1;
    Uint32 flags = SDL_RENDERER_ACCELERATED;
};

class BetterInit {
    private:
        SDL_Window* window;
        SDL_Renderer* render;
    public:
        static int loadSDL(WindowConfig wCfg, RenderConfig rCfg, SDL_Window* &getWindow, SDL_Renderer* &getRender);
        static int loadSDLwithGamepad(WindowConfig wCfg, RenderConfig rCfg, SDL_GameController* &getController, SDL_Window* &getWindow, SDL_Renderer* &getRender);
        static void unloadSDL(SDL_Renderer* render, SDL_Window* window);
        static void unloadSDLwithGamepad(SDL_Renderer* render, SDL_Window* window, SDL_GameController* gamepad);
};

inline int BetterInit::loadSDL(WindowConfig wCfg, RenderConfig rCfg, SDL_Window* &getWindow, SDL_Renderer* &getRender) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Oh no )= ~> " << SDL_GetError() << std::endl;
        return 1;
    }

    getWindow = SDL_CreateWindow(
        wCfg.title, 
        wCfg.x, 
        wCfg.y, 
        wCfg.w, 
        wCfg.h, 
        wCfg.flags
    );

    if (!getWindow) {
        std::cerr << "But Why? Because " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    getRender = SDL_CreateRenderer(
        getWindow, 
        rCfg.index, 
        rCfg.flags
    );

    if (!getRender) {
        std::cerr << "But Why!? Because " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(getWindow);
        SDL_Quit();
        return 1;
    }

    return 0;
}

inline int BetterInit::loadSDLwithGamepad(WindowConfig wCfg, RenderConfig rCfg, SDL_GameController* &getController, SDL_Window* &getWindow, SDL_Renderer* &getRender) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0) {
        std::cerr << "Oh no )= ~> " << SDL_GetError() << std::endl;
        return 1;
    }

    getWindow = SDL_CreateWindow(
        wCfg.title, 
        wCfg.x, 
        wCfg.y, 
        wCfg.w, 
        wCfg.h, 
        wCfg.flags
    );

    if (!getWindow) {
        std::cerr << "But Why? Because " << SDL_GetError() << std::endl;
        SDL_GameControllerClose(getController);
        SDL_Quit();
        return 1;
    }

    getRender = SDL_CreateRenderer(
        getWindow, 
        rCfg.index, 
        rCfg.flags
    );

    if (!getRender) {
        std::cerr << "But Why!? Because " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(getWindow);
        SDL_Quit();
        SDL_GameControllerClose(getController);
        return 1;
    }

    getController = SDL_GameControllerOpen(0);
    

    return 0;
}

inline void BetterInit::unloadSDL(SDL_Renderer* render, SDL_Window* window) {
    if (render)  SDL_DestroyRenderer(render);
    if (window)  SDL_DestroyWindow(window);
}

inline void BetterInit::unloadSDLwithGamepad(SDL_Renderer* render, SDL_Window* window, SDL_GameController* gamepad) {
    if (gamepad) SDL_GameControllerClose(gamepad);
    if (render)  SDL_DestroyRenderer(render);
    if (window)  SDL_DestroyWindow(window);
}