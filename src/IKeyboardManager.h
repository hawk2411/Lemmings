#ifndef _KEYBOARDMANAGER_INCLUDE
#define _KEYBOARDMANAGER_INCLUDE
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

struct IKeyboardManager {

public:

    virtual ~IKeyboardManager() = default;

    virtual void onKeyPressed(const SDL_KeyboardEvent& keyboardEvent)=0;

};

#endif // _KEYBOARDMANAGER_INCLUDE