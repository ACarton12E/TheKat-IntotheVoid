#include "assets.h"
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <fstream>
#include <iostream>
#include <nlohmann/json_fwd.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

void Assets::LoadAll(SDL_Renderer *render) {

    char* basePath = SDL_GetBasePath();
    std::string basePathStr = "";
    std::string CurrentKat;

    if (basePath) {
        basePathStr = std::string(basePath);
        CurrentKat = std::string(basePath) + "assets/json/players/thekat.json";
        SDL_free(basePath);
    } else {
        CurrentKat = CurrentKat;
    }

    std::ifstream file(CurrentKat);
    if (!file.is_open()) {
        std::cerr << "Ah :( " <<  CurrentKat << " Not Found" << std::endl;
        return;
    } else {
        std::cerr << "okey! " <<  CurrentKat << " Found it!" << std::endl;
    }

    nlohmann::json data;
    file >> data;

    std::string idle = basePathStr + data["Animations"]["Idle"].get<std::string>();
    std::cerr << "okey! " <<  idle << " loaded" << std::endl;

    std::string walk = basePathStr + data["Animations"]["Walk"].get<std::string>();
    std::cerr << "okey! " <<  walk << " loaded" << std::endl;

    std::string jump = basePathStr + data["Animations"]["Jump"].get<std::string>();
    std::cerr << "okey! " <<  jump << " loaded" << std::endl;

    std::string fall = basePathStr + data["Animations"]["Fall"].get<std::string>();
    std::cerr << "okey! " <<  fall << " loaded" << std::endl;

    std::string swim = basePathStr + data["Animations"]["Swim"].get<std::string>();
    std::cerr << "okey! " <<  swim << " loaded" << std::endl;


    PlayerAnim::idle = IMG_LoadTexture(render, idle.c_str());
    if (!PlayerAnim::idle) std::cerr << "ah :( " <<  IMG_GetError() << std::endl;

    PlayerAnim::walk = IMG_LoadTexture(render, walk.c_str());
    if (!PlayerAnim::walk) std::cerr << "ah :( " <<  IMG_GetError() << std::endl;

    PlayerAnim::jump = IMG_LoadTexture(render, jump.c_str());
    if (!PlayerAnim::jump) std::cerr << "ah :( " <<  IMG_GetError() << std::endl;

    PlayerAnim::fall = IMG_LoadTexture(render, fall.c_str());
    if (!PlayerAnim::fall) std::cerr << "ah :( " <<  IMG_GetError() << std::endl;

    PlayerAnim::swim = IMG_LoadTexture(render, swim.c_str());
    if (!PlayerAnim::swim) std::cerr << "ah :( " <<  IMG_GetError() << std::endl;

    for (int i = 0; i < 8; i++) {
        Platforms[i] = IMG_LoadTexture(render, ("src/assets/Images/Platforms/" + std::to_string(i + 1) + ".png").c_str());
    };

    for (int i = 0; i < 13; i++) {
        Collectoon::Food[i] = IMG_LoadTexture(render, ("src/assets/Images/Collectoon/Food/" + std::to_string(i + 1) + ".png").c_str());
    };

    UI::Game::PanelPoints = IMG_LoadTexture(render, "src/assets/Images/UI/Game/pointpanel.png");
    UI::Game::PanelMultip = IMG_LoadTexture(render, "src/assets/Images/UI/Game/multpanel.png");

    Background = IMG_LoadTexture(render, "src/assets/Images/Backgrounds/background.png");

    UI::Fonts::eas_analog = TTF_OpenFont("src/assets/Fonts/eas-vhs.ttf", 42);
    UI::Fonts::monogram_ext = TTF_OpenFont("src/assets/Fonts/monogram-extended.ttf", 42);
    UI::Fonts::uniex_mono = TTF_OpenFont("src/assets/Fonts/UnifontExMono.ttf", 42);

    Musics::IntotheVoid = Mix_LoadMUS("src/assets/Audio/Music/Music.ogg");
    if (!Musics::IntotheVoid) {
        std::cerr << "ah :( " <<  Mix_GetError() << std::endl;
    }
    

}