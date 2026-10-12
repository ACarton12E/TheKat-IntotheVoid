#include "assets.h"
#include "../../include/SDL2/SDL_ttf.h"
#include "../../plugins/JSON/json.hpp"
#include "../../include/SDL2/SDL_mixer.h"
#include "../../include/SDL2/SDL_image.h"
#include <string>

void Assets::LoadAll(SDL_Renderer *render) {

    std::string CurrentKat;
    std::string prefix = "";

#ifdef __ANDROID__
    CurrentKat = "assets/json/players/thekat.json";
    prefix = "";
#else
    char* basePath = SDL_GetBasePath();
    if (basePath) {
        CurrentKat = std::string(basePath) + "assets/json/players/thekat.json";
        prefix = std::string(basePath);
        SDL_free(basePath);
    } else {
        CurrentKat = "src/assets/json/players/thekat.json";
        prefix = "src/";
    }
#endif

    SDL_RWops* fileOps = SDL_RWFromFile(CurrentKat.c_str(), "rb");
    if (!fileOps) {
        SDL_Log("Ah :( %s Not Found: %s", CurrentKat.c_str(), SDL_GetError());
        return;
    } else {
        SDL_Log("okey! %s Found it!", CurrentKat.c_str());
    }

    Sint64 fileSize = SDL_RWsize(fileOps);
    std::string fileBuffer(fileSize, '\0');
    SDL_RWread(fileOps, &fileBuffer[0], 1, fileSize);
    SDL_RWclose(fileOps);

    nlohmann::json data = nlohmann::json::parse(fileBuffer);

    std::string iconpath = prefix + "assets/Image/Other/ico.png";
    icon = IMG_Load(iconpath.c_str());

    std::string idle = prefix + data["Animations"]["Idle"].get<std::string>();
    std::string walk = prefix + data["Animations"]["Walk"].get<std::string>();
    std::string jump = prefix + data["Animations"]["Jump"].get<std::string>();
    std::string fall = prefix + data["Animations"]["Fall"].get<std::string>();
    std::string swim = prefix + data["Animations"]["Swim"].get<std::string>();

    PlayerAnim::idle = IMG_LoadTexture(render, idle.c_str());
    PlayerAnim::walk = IMG_LoadTexture(render, walk.c_str());
    PlayerAnim::jump = IMG_LoadTexture(render, jump.c_str());
    PlayerAnim::fall = IMG_LoadTexture(render, fall.c_str());
    PlayerAnim::swim = IMG_LoadTexture(render, swim.c_str());

    for (int i = 0; i < 8; i++) {
        std::string platpath = prefix + "assets/Images/Platforms/" + std::to_string(i + 1) + ".png";
        Platforms[i] = IMG_LoadTexture(render, platpath.c_str());
    }

    for (int i = 0; i < 13; i++) {
        std::string collpath = prefix + "assets/Images/Collectoon/Food/" + std::to_string(i + 1) + ".png";
        Collectoon::Food[i] = IMG_LoadTexture(render, collpath.c_str());
    }

    std::string panelppath = prefix + "assets/Images/UI/Game/pointpanel.png";
    std::string panelmpath = prefix + "assets/Images/UI/Game/multpanel.png";

    UI::Game::PanelPoints = IMG_LoadTexture(render, panelppath.c_str());
    UI::Game::PanelMultip = IMG_LoadTexture(render, panelmpath.c_str());

    std::string back = prefix + "assets/Images/Backgrounds/background.png"; 
    Background = IMG_LoadTexture(render, back.c_str());

    std::string analogeas = prefix + "assets/Fonts/eas-vhs.ttf"; 
    std::string monogramext = prefix + "assets/Fonts/monogram-extended.ttf"; 
    std::string uniexmono = prefix + "assets/Fonts/UnifontExMono.ttf"; 

    UI::Fonts::eas_analog = TTF_OpenFont(analogeas.c_str(), 42);
    UI::Fonts::monogram_ext = TTF_OpenFont(monogramext.c_str(), 42);
    UI::Fonts::uniex_mono = TTF_OpenFont(uniexmono.c_str(), 42);
    
    std::string music = prefix + "assets/Audio/Music/Music.ogg";
    Musics::IntotheVoid = Mix_LoadMUS(music.c_str());
    if (!Musics::IntotheVoid) {
        SDL_Log("ah :( Mix_LoadMUS error: %s", Mix_GetError());
    }
}
