#ifndef _GAMESTATE_INCLUDE
#define _GAMESTATE_INCLUDE

#include "IMouseManager.h"
#include "IKeyboardManager.h"
class Game;

class GameState : public IKeyboardManager, public IMouseManager {

public:
    GameState(Game *game);
    ~GameState() override;

    virtual void init() = 0;

    virtual void update(int deltaTime) = 0;

    virtual void render() = 0;

    void onMouseMove(const SDL_MouseMotionEvent& motionEvent)override;

    void onMouseButtonDown(const SDL_MouseButtonEvent &buttonEvent) override;

    void onMouseButtonUp(const SDL_MouseButtonEvent &buttonEvent) override;

protected:
    float _currentTime;
    Game *_game;
private:
    // we can have access at any time
    int mouseX, mouseY;               // Mouse position

};


#endif // _GAMESTATE_INCLUDE

