#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_gamecontroller.h>
#include <cstring>

class BetterInput {
    public:
        class Keyboard {
            public:
            static bool onJustPressed(const SDL_Event &event, SDL_Scancode key);

            static bool onPressed(SDL_Scancode key);

            static bool onRelease(const SDL_Event &event, SDL_Scancode key);

            static bool onJustRelease(const SDL_Event &event, SDL_Scancode key);
        };

        class Mouse {
            public:
            static bool onJustPressed(const SDL_Event& event, Uint8 button);
            static bool onJustPressedwithPosition(const SDL_Event& event, Uint8 button, SDL_Point &mousepos);

            static bool onPressed(Uint8 button);
            static bool onPressedwithPosition(Uint8 button, SDL_Point &mousepos);

            static bool onRelease(const SDL_Event& event, Uint8 button);
        };
        
        class Gamepad {
            public:
                static bool onJustPressed(const SDL_Event& event, int controller, SDL_GameControllerButton button);
                static bool onPressed(int controller, SDL_GameControllerButton button);
                static bool onRelease(const SDL_Event& event, int controller, SDL_GameControllerButton button);
        };
};

static Uint8 prev_keystate[SDL_NUM_SCANCODES] = {0};
static bool keystate_init = false;

inline bool BetterInput::Keyboard::onJustPressed(const SDL_Event &event, SDL_Scancode key) {
    const Uint8* current_keystate = SDL_GetKeyboardState(NULL);

    if (!keystate_init) {
        std::memcpy(prev_keystate, current_keystate, SDL_NUM_SCANCODES);
        keystate_init = true;
    }

    bool pressed = (current_keystate[key] == 1) && (prev_keystate[key] == 0);

    prev_keystate[key] = current_keystate[key];
    
    return pressed;
}


inline bool BetterInput::Keyboard::onPressed(SDL_Scancode key) {
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    return keystate[key] == 1;
}

inline bool BetterInput::Keyboard::onRelease(const SDL_Event &event, SDL_Scancode key) {
    if (event.type == SDL_KEYUP) {
        if (event.key.keysym.scancode == key) {
            return true;
        }
    }
    return false;
}

inline bool BetterInput::Keyboard::onJustRelease(const SDL_Event &event, SDL_Scancode key) {
    if (event.type == SDL_KEYUP && event.key.repeat == 0) {
        if (event.key.keysym.scancode == key) {
            return true;
        }
    }
    return false;
}

// Input Mouse

inline bool BetterInput::Mouse::onJustPressed(const SDL_Event &event, Uint8 button) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == button) {
            return true;
        }
    }
    return false;
}
 
static Uint32 prev_mousestate = 0;

inline bool BetterInput::Mouse::onJustPressedwithPosition(const SDL_Event &event, Uint8 button, SDL_Point &mousepos) {
    Uint32 current_mousestate = SDL_GetMouseState(&mousepos.x, &mousepos.y);
    Uint32 mask = 0;

    if (button == SDL_BUTTON_LEFT)   mask = SDL_BUTTON_LMASK;
    if (button == SDL_BUTTON_RIGHT)  mask = SDL_BUTTON_RMASK;
    if (button == SDL_BUTTON_MIDDLE) mask = SDL_BUTTON_MMASK;

    bool pressed = (current_mousestate & mask) && !(prev_mousestate & mask);
    
    prev_mousestate = current_mousestate;
    return pressed;
}
 

inline bool BetterInput::Mouse::onPressed(Uint8 button) {
    Uint32 buttonsState = SDL_GetMouseState(NULL, NULL);

    if (button == SDL_BUTTON_LEFT)   return (buttonsState & SDL_BUTTON_LMASK);
    if (button == SDL_BUTTON_RIGHT)  return (buttonsState & SDL_BUTTON_RMASK);
    if (button == SDL_BUTTON_MIDDLE) return (buttonsState & SDL_BUTTON_MMASK);
    
    return false;
}
 

inline bool BetterInput::Mouse::onPressedwithPosition(Uint8 button, SDL_Point &mousepos) {
    
    Uint32 buttonsState = SDL_GetMouseState(&mousepos.x, &mousepos.y);

    if (button == SDL_BUTTON_LEFT)   return (buttonsState & SDL_BUTTON_LMASK);
    if (button == SDL_BUTTON_RIGHT)  return (buttonsState & SDL_BUTTON_RMASK);
    if (button == SDL_BUTTON_MIDDLE) return (buttonsState & SDL_BUTTON_MMASK);
    
    return false;
}

inline bool BetterInput::Mouse::onRelease(const SDL_Event &event, Uint8 button) {
    if (event.type == SDL_MOUSEBUTTONUP) {
        if (event.button.button == button) {
            return true;
        }
    }
    return false;
}

// Input Gamepad

static Uint8 prev_padstate[4][SDL_CONTROLLER_BUTTON_MAX] = {{0}};

inline bool BetterInput::Gamepad::onJustPressed(const SDL_Event &event, int controller, SDL_GameControllerButton button) {
    SDL_GameController* pad = SDL_GameControllerFromInstanceID(controller);
    if (pad == nullptr) return false;

    Uint8 current_button_state = SDL_GameControllerGetButton(pad, button);
    bool pressed = (current_button_state == 1) && (prev_padstate[controller][button] == 0);
    
    prev_padstate[controller][button] = current_button_state;
    return pressed;
}

inline bool BetterInput::Gamepad::onPressed(int controller, SDL_GameControllerButton button) {

    SDL_GameController* pad = SDL_GameControllerFromInstanceID(controller);
    
    if (pad == nullptr) return false;

    return SDL_GameControllerGetButton(pad, button) == 1;
}

inline bool BetterInput::Gamepad::onRelease(const SDL_Event &event, int controller, SDL_GameControllerButton button) {
    if (event.cbutton.type == SDL_CONTROLLERBUTTONUP) {
        if (event.cbutton.which == controller) {
            if (event.cbutton.button == button) {
                return true;
            }
        }
    }

    return false;
}