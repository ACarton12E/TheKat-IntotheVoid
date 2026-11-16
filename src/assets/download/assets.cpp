#include "assets.h"
#include "../../include/SDL2/SDL_ttf.h"
#include "../../plugins/JSON/json.hpp"
#include "../../include/SDL2/SDL_mixer.h"
#include "../../include/SDL2/SDL_image.h"
#include "../../Global.h"
#include <string>

void Assets::LoadCurrent(SDL_Renderer *render, std::string JSONpath) {
    CurrentKat = "";

    #ifdef __ANDROID__
        CurrentKat = JSONpath;
    #else
        char* basePath = SDL_GetBasePath();
        if (basePath) {
            CurrentKat = std::string(basePath) + JSONpath;
            SDL_free(basePath);
        } else {
            CurrentKat = "src/" + JSONpath;
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

    // PLAYER

    std::string idle =        prefix + data["Animations"]["Normal"]["Idle"].get<std::string>();
    std::string walk =        prefix + data["Animations"]["Normal"]["Walk"].get<std::string>();
    std::string jump =        prefix + data["Animations"]["Normal"]["Jump"].get<std::string>();
    std::string fall =        prefix + data["Animations"]["Normal"]["Fall"].get<std::string>();
    std::string swim =        prefix + data["Animations"]["Normal"]["Swim"].get<std::string>();
    std::string flying =      prefix + data["Animations"]["Normal"]["Flying"].get<std::string>();
    std::string badFlying =   prefix + data["Animations"]["Normal"]["BadFlying"].get<std::string>();
    std::string splashfloor = prefix + data["Animations"]["Normal"]["FloorSplash"].get<std::string>();
    std::string damage =      prefix + data["Animations"]["Normal"]["Damage"].get<std::string>();

    PlayerAnim::idle                = IMG_LoadTexture(render, idle.c_str());
    PlayerAnim::walk                = IMG_LoadTexture(render, walk.c_str());
    PlayerAnim::jump                = IMG_LoadTexture(render, jump.c_str());
    PlayerAnim::fall                = IMG_LoadTexture(render, fall.c_str());
    PlayerAnim::swim                = IMG_LoadTexture(render, swim.c_str());
    PlayerAnim::flying              = IMG_LoadTexture(render, flying.c_str());
    PlayerAnim::badFlying           = IMG_LoadTexture(render, badFlying.c_str());
    PlayerAnim::splashFloor         = IMG_LoadTexture(render, splashfloor.c_str());
    PlayerAnim::damage              = IMG_LoadTexture(render, damage.c_str());

    std::string idleaske =   prefix + data["Animations"]["ASKE"]["Idle"].get<std::string>();
    std::string walkaske =   prefix + data["Animations"]["ASKE"]["Walk"].get<std::string>();
    std::string jumpaske =   prefix + data["Animations"]["ASKE"]["Jump"].get<std::string>();
    std::string fallaske =   prefix + data["Animations"]["ASKE"]["Fall"].get<std::string>();
    std::string swimaske =   prefix + data["Animations"]["ASKE"]["Swim"].get<std::string>();

    std::string gun =        prefix + data["Animations"]["Armors"][std::to_string(Global::CurrentArmor)].get<std::string>();

    PlayerAnim::ASKE::idle          = IMG_LoadTexture(render, idleaske.c_str());
    PlayerAnim::ASKE::walk          = IMG_LoadTexture(render, walkaske.c_str());
    PlayerAnim::ASKE::jump          = IMG_LoadTexture(render, jumpaske.c_str());
    PlayerAnim::ASKE::fall          = IMG_LoadTexture(render, fallaske.c_str());
    PlayerAnim::ASKE::swim          = IMG_LoadTexture(render, swimaske.c_str());

    PlayerAnim::ASKE::gun           = IMG_LoadTexture(render, gun.c_str());

    std::string shootsound = prefix + data["ARMOR_PROPERTYS"][std::to_string(Global::CurrentArmor)]["sound"].get<std::string>();

    PlayerAnim::ASKE::sound         = Mix_LoadWAV(shootsound.c_str());

    if (!PlayerAnim::ASKE::gun) {
        SDL_Log("uhhhh: %s", SDL_GetError());
    }

    std::string sight = prefix + "assets/Images/UI/Game/ASKE/sight.png";
    PlayerAnim::ASKE::sight = IMG_LoadTexture(render, sight.c_str());

    // Guns Data

    Global::ArmorData::name = data["ARMOR_PROPERTYS"][std::to_string(Global::CurrentArmor)]["name"].get<std::string>();
    Global::ArmorData::size = data["ARMOR_PROPERTYS"][std::to_string(Global::CurrentArmor)]["size"].get<float>();
    Global::ArmorData::cooldown = data["ARMOR_PROPERTYS"][std::to_string(Global::CurrentArmor)]["cooldown"].get<float>();
    Global::ArmorData::canPressed = data["ARMOR_PROPERTYS"][std::to_string(Global::CurrentArmor)]["canpress"].get<bool>();

    auto& particleData = data["ARMOR_PROPERTYS"][std::to_string(Global::CurrentArmor)]["particles"];

    Global::ArmorData::Particles::active = particleData["active"].get<bool>();
    Global::ArmorData::Particles::fire   = particleData["fire"].get<bool>();
    Global::ArmorData::Particles::count  = particleData["count"].get<int>();


    if (!particleData["assets"].is_null()) {
        std::string assetsparticlearmor = prefix + particleData["assets"].get<std::string>();
        Global::ArmorData::Particles::assets = IMG_LoadTexture(render, assetsparticlearmor.c_str());
    } else {
        Global::ArmorData::Particles::assets = nullptr;
    }
}

void Assets::LoadAll(SDL_Renderer *render) {

    prefix = "";

#ifdef __ANDROID__
    prefix = "";
#else
    char* basePath = SDL_GetBasePath();
    if (basePath) {
        prefix = std::string(basePath);
        SDL_free(basePath);
    } else {
        prefix = "src/";
    }
#endif



    std::string iconpath = prefix + "assets/Images/Other/ico.png";
    
    icon = IMG_Load(iconpath.c_str());

    std::string logopath = prefix + "assets/Images/UI/logo.png";

    Logo = IMG_LoadTexture(render, logopath.c_str());

    // OBJECTS

    for (int i = 0; i < 8; i++) {
        std::string platpath = prefix + "assets/Images/Platforms/" + std::to_string(i + 1) + ".png";
        Platforms[i]                = IMG_LoadTexture(render, platpath.c_str());
    }

    for (int i = 0; i < 13; i++) {
        std::string collpath = prefix + "assets/Images/Collectoon/Food/" + std::to_string(i + 1) + ".png";
        Collectoon::Food[i]         = IMG_LoadTexture(render, collpath.c_str());
    }

    std::string playpanel = prefix + "assets/Images/UI/Menu/new/play/play.png";
    std::string shoppanel = prefix + "assets/Images/UI/Menu/new/play/shop.png";
    std::string questpanel = prefix + "assets/Images/UI/Menu/new/play/quest.png";
    std::string advpanel = prefix + "assets/Images/UI/Menu/new/play/adv.png";
    std::string quitpanel = prefix + "assets/Images/UI/Menu/new/exit/exit.png";

    UI::Menu::Play                  = IMG_LoadTexture(render, playpanel.c_str());
    UI::Menu::Shop                  = IMG_LoadTexture(render, shoppanel.c_str());
    UI::Menu::Quest                 = IMG_LoadTexture(render, questpanel.c_str());
    UI::Menu::Adv                   = IMG_LoadTexture(render, advpanel.c_str());

    UI::Menu::Quit                  = IMG_LoadTexture(render, quitpanel.c_str());

    std::string panelppath = prefix + "assets/Images/UI/Game/pointpanel.png";
    std::string panelmpath = prefix + "assets/Images/UI/Game/multpanel.png";

    UI::Game::PanelPoints           = IMG_LoadTexture(render, panelppath.c_str());
    UI::Game::PanelMultip           = IMG_LoadTexture(render, panelmpath.c_str());

    std::string statusp = prefix + "assets/Images/UI/Game/Status/panel.png";
    std::string liveroul = prefix + "assets/Images/UI/Game/Status/live.png";
    std::string durroul = prefix + "assets/Images/UI/Game/Status/dur.png";
    std::string enerroul = prefix + "assets/Images/UI/Game/Status/energy.png";

    UI::Game::Status::StatusPanel   = IMG_LoadTexture(render, statusp.c_str());
    UI::Game::Status::LiveRoulete   = IMG_LoadTexture(render, liveroul.c_str());
    UI::Game::Status::DurRoulete    = IMG_LoadTexture(render, durroul.c_str());
    UI::Game::Status::EnergyRoulete = IMG_LoadTexture(render, enerroul.c_str());

    std::string back = prefix + "assets/Images/Backgrounds/background.png"; 
    Background                      = IMG_LoadTexture(render, back.c_str());

    std::string analogeas = prefix + "assets/Fonts/eas-vhs.ttf"; 
    std::string monogramext = prefix + "assets/Fonts/monogram-extended.ttf"; 
    std::string uniexmono = prefix + "assets/Fonts/UnifontExMono.ttf"; 

    UI::Fonts::eas_analog           = TTF_OpenFont(analogeas.c_str(), 42);
    UI::Fonts::monogram_ext         = TTF_OpenFont(monogramext.c_str(), 42);
    UI::Fonts::uniex_mono           = TTF_OpenFont(uniexmono.c_str(), 28);
    

    std::string fishoder = prefix + "assets/Images/Enemies/Fishoder/fishoder.png";
    Enemies::Fishoder::Normal       = IMG_LoadTexture(render, fishoder.c_str());

    std::string shadowner = prefix + "assets/Images/Enemies/Shadowner/shadowner.png";
    Enemies::Shadowner::Normal      = IMG_LoadTexture(render, shadowner.c_str());

    std::string spikader = prefix + "assets/Images/Enemies/Spikader/spikader.png";
    Enemies::Spikader::Normal       = IMG_LoadTexture(render, spikader.c_str());

    std::string waternormal = prefix + "assets/Images/Water/water.png";
    Water::Normal                   = IMG_LoadTexture(render, waternormal.c_str());

    // FX

    std::string explote = prefix + "assets/Images/Particles/Explotion.png";
    FX::Explotion = IMG_LoadTexture(render, explote.c_str());

    // SOUNDS AND MUSIC

    std::string music = prefix + "assets/Audio/Music/Music2.ogg";
    Musics::IntotheVoid = Mix_LoadMUS(music.c_str());
    if (!Musics::IntotheVoid) {
        SDL_Log("ah :( Mix_LoadMUS error: %s", Mix_GetError());
    }

    std::string burn = prefix + "assets/Audio/Music/Power1.ogg";
    Musics::Burnyan = Mix_LoadMUS(burn.c_str());
    if (!Musics::IntotheVoid) {
        SDL_Log("ah :( Mix_LoadMUS error: %s", Mix_GetError());
    }

    std::string damagesound = prefix + "assets/Audio/Sounds/damage.ogg";
    Sounds::Damage = Mix_LoadWAV(damagesound.c_str());

    std::string damagesoundenemie = prefix + "assets/Audio/Sounds/damageenemie.ogg";
    Sounds::DamageEnemie = Mix_LoadWAV(damagesoundenemie.c_str());

    std::string explotionsound = prefix + "assets/Audio/Sounds/explotion.ogg";
    Sounds::Explotion = Mix_LoadWAV(explotionsound.c_str());

    std::string katchedsound = prefix + "assets/Audio/Sounds/Food.ogg";
    Sounds::Katched = Mix_LoadWAV(katchedsound.c_str());

}
