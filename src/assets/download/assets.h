#pragma once
#include "../../include/SDL2/SDL_render.h"
#include "../../include/SDL2/SDL_ttf.h"
#include <string>
#include "../../include/SDL2/SDL_mixer.h"



namespace Assets {

    inline std::string CurrentKat;
    inline SDL_Texture* Logo;
    inline std::string prefix;

    namespace Musics {
        inline Mix_Music* IntotheVoid;

        inline Mix_Music* Burnyan;
    }

    namespace Sounds {
        inline Mix_Chunk* Damage;
        inline Mix_Chunk* DamageEnemie;
        inline Mix_Chunk* Explotion;
        inline Mix_Chunk* Katched;
    }

    namespace PlayerAnim {
        inline SDL_Texture* idle;
        inline SDL_Texture* walk;
        inline SDL_Texture* jump;
        inline SDL_Texture* fall;
        inline SDL_Texture* swim;
        inline SDL_Texture* flying;
        inline SDL_Texture* badFlying;
        inline SDL_Texture* splashFloor;
        inline SDL_Texture* damage;

        namespace ASKE {
            inline SDL_Texture* idle;
            inline SDL_Texture* walk;
            inline SDL_Texture* jump;
            inline SDL_Texture* fall;
            inline SDL_Texture* swim;

            inline SDL_Texture* gun;
            inline SDL_Texture* sight;

            inline Mix_Chunk* sound;
        }
    };

    inline SDL_Texture* Background;
    inline SDL_Texture* Platforms[8];
    inline SDL_Surface* icon;

    namespace Collectoon {
        inline SDL_Texture* Food[13];

        inline SDL_Texture* Aloy;

        inline SDL_Texture* Disk;
    };

    namespace FX {
        inline SDL_Texture* Explotion;
    }

    namespace Enemies {
        namespace Fishoder {
            inline SDL_Texture* Normal;
            inline SDL_Texture* Ouch;
        }
        namespace Shadowner {
            inline SDL_Texture* Normal;
            inline SDL_Texture* Ouch;
        }
        namespace Spikader {
            inline SDL_Texture* Normal;
        }
    }

    namespace Water {
        inline SDL_Texture* Normal;
    }

    namespace UI {

        namespace Game {
            inline SDL_Texture* PanelPoints;
            inline SDL_Texture* PanelMultip;

            namespace Status {
                inline SDL_Texture* StatusPanel;
                inline SDL_Texture* LiveRoulete;
                inline SDL_Texture* DurRoulete;
                inline SDL_Texture* EnergyRoulete;
            }
        }

        namespace Menu {
            inline SDL_Texture* Play;
            inline SDL_Texture* Shop;
            inline SDL_Texture* Quest;
            inline SDL_Texture* Adv;

            inline SDL_Texture* Quit;
        }

        namespace Fonts {
            inline TTF_Font* eas_analog;
            inline TTF_Font* uniex_mono;
            inline TTF_Font* monogram_ext;
        };
    };

    void LoadAll(SDL_Renderer* render);
    void LoadCurrent(SDL_Renderer* render, std::string JSONpath);
    //void SetCurrentKat(const std::string& jsonPath);
}