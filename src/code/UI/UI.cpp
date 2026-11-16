#include "UI.h"
#include "../../plugins/betterInput/betterInput.hpp"
#include "../../Global.h"

std::string UI::playerStatus = "Normal";
float UI::timeleftdt = 0;
bool UI::eatedFrame = false;
float UI::opacityflash = 0;
float UI::negativeflash = 255;
float UI::durvalue = 0;

char* floatToString(float value) {
    static char buffer[32];
    snprintf(buffer, sizeof(buffer), "%.2f", value);
    return buffer;
}

char* format(float value) {
    static char buffer[32];

    long long num = std::roundf(value);

    long long M = (num / 100000) % 1000;
    long long k = (num / 1000) % 1000;
    long long u = num % 1000;

    snprintf(buffer, sizeof(buffer), "%03lld.%03lld.%03lld", M, k, u);
    return buffer;
}

SDL_Texture* UI::textState = nullptr;
std::string UI::lastState = "";
SDL_Rect UI::destState = {0,0,0,0};

SDL_Texture* UI::textPoints = nullptr;
long long UI::lastPoints = -1;
SDL_Rect UI::destPoints = {0,0,0,0};

SDL_Texture* UI::textMultp = nullptr;
float UI::lastMultp = 1;
SDL_Rect UI::destMultp = {0,0,0,0};

void UI::Preload(SDL_Renderer *render) {
    Clean();

    SDL_Color colortext = {255, 255, 255, 255};

    playerStatus = "Normal";
    if (Assets::UI::Fonts::uniex_mono) {
        SDL_Surface* surfState = TTF_RenderText_Solid(Assets::UI::Fonts::uniex_mono, playerStatus.c_str(), colortext);
        if (surfState) {
            textState = SDL_CreateTextureFromSurface(render, surfState);
            destState = { 27, 27, surfState->w, surfState->h };
            SDL_FreeSurface(surfState);
        }

        SDL_Surface* sOuch = TTF_RenderText_Solid(Assets::UI::Fonts::uniex_mono, "Ouch!!", colortext);
        if (sOuch) {
            SDL_DestroyTexture(SDL_CreateTextureFromSurface(render, sOuch));
            SDL_FreeSurface(sOuch);
        }

        SDL_Surface* sFish = TTF_RenderText_Solid(Assets::UI::Fonts::uniex_mono, "Fisheated!!", colortext);
        if (sFish) {
            SDL_DestroyTexture(SDL_CreateTextureFromSurface(render, sFish));
            SDL_FreeSurface(sFish);
        }
    }
    lastState = playerStatus;

    lastPoints = 0;
    lastMultp = -1;
    if (Assets::UI::Fonts::eas_analog) {
        SDL_Surface* surfPoints = TTF_RenderText_Solid(Assets::UI::Fonts::eas_analog, format(0), colortext);
        if (surfPoints) {
            textPoints = SDL_CreateTextureFromSurface(render, surfPoints);
            destPoints = { 0, 25, surfPoints->w, surfPoints->h };
            SDL_FreeSurface(surfPoints);
        }

        SDL_Surface* surfMltp = TTF_RenderText_Solid(Assets::UI::Fonts::eas_analog, "1", colortext);
        if (surfMltp) {
            textMultp = SDL_CreateTextureFromSurface(render, surfMltp);
            destMultp = { 0, 25, surfMltp->w, surfMltp->h };
            SDL_FreeSurface(surfMltp);
        }
    }
}

void UI::Renderize(
    float dt,
    SDL_Event event,
    SDL_Window *window,
    SDL_Renderer *render,
    float points,
    float lives,
    Player *player
    ) {

    if (!player || !render || !window) return;


    int livesframe = (lives * 8) / 100;

    int windoww, windowh;
    SDL_GetWindowSize(window, &windoww, &windowh);

    // POINTS PANEL
    SDL_Rect srcp = { 0, 0, 320, 128 };
    SDL_Rect destp = { windoww - 320, 15, 320, 128 };
    SDL_RenderCopy(render, Assets::UI::Game::PanelPoints, &srcp, &destp);

    // MULTP PANEL
    SDL_Rect srcm = { 0, 0, 140, 107 };
    SDL_Rect destm = { windoww - 170, 110, 140, 107 };
    SDL_RenderCopy(render, Assets::UI::Game::PanelMultip, &srcm, &destm);

    timeleftdt += dt;

    if (player->fisheated) {
        int currentFrameFish = (int)(timeleftdt * 12) % 4;

        SDL_Rect srcfish = { 160 * currentFrameFish, 0, 160, 140 };
        float positiony = ((float)windowh / 4) + cos((timeleftdt * 20) * 0.5);
        SDL_FRect destfish = { 15, positiony, 320, 280 };
        float rotate = sin((timeleftdt * 20) * 0.5);
        SDL_FPoint fishpoint = {160, 140};

        SDL_RenderCopyExF(
            render,
            Assets::Enemies::Fishoder::Normal,
            &srcfish,
            &destfish,
            rotate,
            &fishpoint,
            SDL_FLIP_HORIZONTAL
            );

        if (currentFrameFish == 3 && !eatedFrame) {
            player->lives -= 1;
            eatedFrame = true;
        } else if (currentFrameFish != 3) {
            eatedFrame = false;
        }
    }

    if (opacityflash > 0.0f) {
        opacityflash -= 260.0f * dt;
        if (opacityflash < 0.0f) opacityflash = 0.0f;
    }

    if (negativeflash < 255.0f) {
        negativeflash += 260.0f * dt;
        if (negativeflash > 255.0f) negativeflash = 255.0f;
    }

    SDL_Rect spsrc = {0, 0, 360, 164};
    SDL_FRect spdest = {15, 15, 360, 164};
    SDL_RenderCopyF(render, Assets::UI::Game::Status::StatusPanel, &spsrc, &spdest);

    if ((playerStatus != lastState || textState == nullptr) && Assets::UI::Fonts::uniex_mono) {
        if (textState) SDL_DestroyTexture(textState);

        SDL_Color colortext = {255, 255, 255, 255};
        SDL_Surface* surfState = TTF_RenderText_Solid(Assets::UI::Fonts::uniex_mono, playerStatus.c_str(), colortext);
        if (surfState) {
            textState = SDL_CreateTextureFromSurface(render, surfState);
            destState = { 27, 27, surfState->w, surfState->h };
            SDL_FreeSurface(surfState);
        }
        lastState = playerStatus;
    }

    if (textState) {
        SDL_RenderCopy(render, textState, NULL, &destState);
    }

    SDL_Rect lrsrc = {livesframe * 128, 0, 128, 144};
    SDL_FRect lrdest = {164, 49, 128, 144};
    SDL_RenderCopyF(render, Assets::UI::Game::Status::LiveRoulete, &lrsrc, &lrdest);

    if (player->currentAction == CurrentAction::Fisheated) {
        durvalue = (player->fishdur * 8) / 7;
        playerStatus = "Fisheated!!";
    } else {
        if (!player->Dead) {
            if (player->CooldownDamage >= 0 && player->wasAttacked) {
                durvalue = (player->CooldownDamage * 8) / 1.5;
                playerStatus = "Ouch!!";
            } else {
                durvalue = 0;
                playerStatus = "Normal";
            }
        } else {
            durvalue = 0;
            playerStatus = "Ded :(";
        }
    }

    SDL_Rect drsrc = {(int)durvalue * 128, 0, 128, 144};
    SDL_FRect drdest = {20, 49, 128, 144};
    SDL_RenderCopyF(render, Assets::UI::Game::Status::DurRoulete, &drsrc, &drdest);

    SDL_Rect ersrc = {0, 0, 54, 60};
    SDL_FRect erdest = {95, 138, 54, 60};
    SDL_RenderCopyF(render, Assets::UI::Game::Status::EnergyRoulete, &ersrc, &erdest);

    SDL_Rect exitsrc = {0, 0, 240, 82};
    SDL_FRect exitdest = {(float)windoww - (155.0f * 1.5f), (float)windowh - (94.0f * 1.5f), 240 * 1.5f, 82 * 1.5f};

    SDL_Point mousepos;
    if (BetterInput::Mouse::onJustPressedwithPosition(event, SDL_BUTTON_LEFT, mousepos)) {
        SDL_FPoint mousefpos = {(float)mousepos.x, (float)mousepos.y};
        if (SDL_PointInFRect(&mousefpos, &exitdest)) {
            Global::CurrentScene = SCENES::MENU;
        }
    }

    SDL_RenderCopyF(render, Assets::UI::Menu::Quit, &exitsrc, &exitdest);

    long long CurrentPoints = std::floor(points);
    if ((CurrentPoints != lastPoints || textPoints == nullptr) && Assets::UI::Fonts::eas_analog) {
        if (textPoints) SDL_DestroyTexture(textPoints);

        SDL_Color colortext = {255, 255, 255, 255};
        SDL_Surface* surfPoints = TTF_RenderText_Solid(Assets::UI::Fonts::eas_analog, format(CurrentPoints), colortext);
        if (surfPoints) {
            textPoints = SDL_CreateTextureFromSurface(render, surfPoints);
            destPoints = { windoww - 280, 25, surfPoints->w, surfPoints->h };
            SDL_FreeSurface(surfPoints);
        }
        lastPoints = CurrentPoints;
    }

    if (textPoints) {
        SDL_RenderCopy(render, textPoints, NULL, &destPoints);
    }

    float CurrentMult = std::floor(player->multiplier);
    if ((CurrentMult != lastMultp || textMultp == nullptr) && Assets::UI::Fonts::eas_analog) {
        if (textMultp) SDL_DestroyTexture(textMultp);

        char multBuffer[16];
        snprintf(multBuffer, sizeof(multBuffer), "%.0f", CurrentMult);

        SDL_Color colortext = {255, 255, 255, 255};
        SDL_Surface* surfMultp = TTF_RenderText_Solid(Assets::UI::Fonts::eas_analog, multBuffer, colortext);
        if (surfMultp) {
            textMultp = SDL_CreateTextureFromSurface(render, surfMultp);
            SDL_SetTextureBlendMode(textMultp, SDL_BLENDMODE_BLEND);
            destMultp = { windoww - 125, 145, (int)(surfMultp->w * 0.75f), (int)(surfMultp->h * 0.75f) };
            SDL_FreeSurface(surfMultp);
        }
        lastMultp = CurrentMult;
    }

    if (textMultp) {
        Uint8 alphaMult = (player->multiplierdur <= 3.0f && player->multiplierdur > 0.0f)
        ? (Uint8)(((sinf(player->multiplierdur * 15.0f) + 1.0f) * 0.5f) * 255.0f)
        : 255;

        SDL_SetTextureAlphaMod(textMultp, alphaMult);
        SDL_RenderCopy(render, textMultp, NULL, &destMultp);
    }

    SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(render, 255, 255, 255, (Uint8)opacityflash);
    SDL_Rect Rect = {0, 0, windoww, windowh};
    SDL_RenderFillRect(render, &Rect);
}

void UI::Clean() {
    if (textState) { SDL_DestroyTexture(textState); textState = nullptr; }
    if (textPoints) { SDL_DestroyTexture(textPoints); textPoints = nullptr; }
    if (textMultp) { SDL_DestroyTexture(textMultp); textMultp = nullptr; }
}
