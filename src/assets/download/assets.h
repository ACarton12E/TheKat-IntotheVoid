#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <SDL2/SDL_mixer.h>



namespace Assets {

    extern std::string CurrentKat;

    namespace Musics {
        inline Mix_Music* IntotheVoid;
    }

    namespace PlayerAnim {
        inline SDL_Texture* idle;
        inline SDL_Texture* walk;
        inline SDL_Texture* jump;
        inline SDL_Texture* fall;
        inline SDL_Texture* swim;
    };

    inline SDL_Texture* Background;
    inline SDL_Texture* Platforms[8];

    namespace Collectoon {
        inline SDL_Texture* Food[13];

        inline SDL_Texture* Aloy;

        inline SDL_Texture* Disk;
    };

    

        /* TODO: namespace Starubela {
        
        } */
    namespace UI {

        namespace Game {
            inline SDL_Texture* PanelPoints;
            inline SDL_Texture* PanelMultip;
        }

        namespace Fonts {
            inline TTF_Font* eas_analog;
            inline TTF_Font* uniex_mono;
            inline TTF_Font* monogram_ext;
        };
    };

    void LoadAll(SDL_Renderer* render);
    void SetCurrentKat(const std::string& jsonPath);
}