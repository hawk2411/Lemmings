#ifndef _GAMESTATE_INCLUDE
#define _GAMESTATE_INCLUDE

#include "MouseManager.h"
#include "IKeyboardManager.h"

class GameState : public IKeyboardManager, public MouseManager {

public:
    GameState();
    ~GameState() override;

    virtual void init() = 0;

    virtual void update(int deltaTime) = 0;

    virtual void render() = 0;

    void mouseMove(int x, int y) override;

    void mousePress(int button) override;

    void mouseRelease(int button) override;

    virtual void mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton) = 0;

protected:
    float _currentTime;

private:
    // we can have access at any time
    int mouseX, mouseY;               // Mouse position
    bool bLeftMouse, bRightMouse;     // Mouse button states
};


#endif // _GAMESTATE_INCLUDE

