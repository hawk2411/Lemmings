#ifndef _MOUSEMANAGER_INCLUDE
#define _MOUSEMANAGER_INCLUDE
#include <SDL2/SDL.h>

class IMouseManager {

public:
    virtual ~IMouseManager()= default;
    virtual void onMouseButtonDown(const SDL_MouseButtonEvent& buttonEvent ) = 0;
    virtual void onMouseButtonUp(const SDL_MouseButtonEvent& buttonEvent)=0;
    virtual void onMouseMove(const SDL_MouseMotionEvent& motionEvent)=0;


    virtual void mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton)=0;
};

#endif // _MOUSEMANAGER_INCLUDE

