#include "assets.h"
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <fstream>
#include <iostream>
#include "../../plugins/JSON/json.hpp"
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
        std::string platpath = basePathStr + ("assets/Images/Platforms/" + std::to_string(i + 1) + ".png");
        Platforms[i] = IMG_LoadTexture(render, platpath.c_str());
    };

    for (int i = 0; i < 13; i++) {
        std::string collpath = basePathStr + ("assets/Images/Collectoon/Food/" + std::to_string(i + 1) + ".png");
        Collectoon::Food[i] = IMG_LoadTexture(render, collpath.c_str());

    };

    std::string panelppath = basePathStr + "assets/Images/UI/Game/pointpanel.png";
    std::string panelmpath = basePathStr + "assets/Images/UI/Game/multpanel.png";

    UI::Game::PanelPoints = IMG_LoadTexture(render, panelppath.c_str());
    UI::Game::PanelMultip = IMG_LoadTexture(render, panelmpath.c_str());

    std::string back = basePathStr + "assets/Images/Backgrounds/background.png"; 

    Background = IMG_LoadTexture(render, back.c_str());

    std::string analogeas = basePathStr + "assets/Fonts/eas-vhs.ttf"; 
    std::string monogramext = basePathStr + "assets/Fonts/monogram-extended.ttf"; 
    std::string uniexmono = basePathStr + "assets/Fonts/UnifontExMono.ttf"; 

    UI::Fonts::eas_analog = TTF_OpenFont(analogeas.c_str(), 42);
    UI::Fonts::monogram_ext = TTF_OpenFont(monogramext.c_str(), 42);
    UI::Fonts::uniex_mono = TTF_OpenFont(uniexmono.c_str(), 42);
    

    std::string music = basePathStr + "assets/Audio/Music/Music.ogg";
    Musics::IntotheVoid = Mix_LoadMUS(music.c_str());
    if (!Musics::IntotheVoid) {
        std::cerr << "ah :( " <<  Mix_GetError() << std::endl;
    }
    

}