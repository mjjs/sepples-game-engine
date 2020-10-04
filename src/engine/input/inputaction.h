#ifndef _SGE_INPUTACTION_H
#define _SGE_INPUTACTION_H

#include <SDL2/SDL_keycode.h>

using event_handler = void (*)();

enum key_event_type {
    HELD,
    SINGLE
};

struct InputAction {
    key_event_type event_type;
    SDL_KeyCode key_code;
    event_handler handler;
};
#endif
