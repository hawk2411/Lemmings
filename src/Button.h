#ifndef _BUTTON_INCLUDE
#define _BUTTON_INCLUDE

#include "Sprite.h"
#include "NumDisplayButton.h"
#include "ShaderManager.h"

class Button {

public:

    enum ButtonNames {
        MINUS_BUTTON,
        PLUS_BUTTON,
        CLIMBER_BUTTON,
        FLOATER_BUTTON,
        EXPLODER_BUTTON,
        BLOCKER_BUTTON,
        BUILDER_BUTTON,
        BASHER_BUTTON,
        MINER_BUTTON,
        DIGGER_BUTTON,
        PAUSE_BUTTON,
        NUKE_BUTTON,
        SPEED_BUTTON
    };

    void init(ShaderManager *shaderManager);

    void render();

    glm::vec2 getPosition();

    void setPosition(glm::vec2 position);

    void setSprite(std::unique_ptr<Sprite> sprite);

    void setNum(int num);


private:
    glm::vec2 _position;
    std::unique_ptr<Sprite> _buttonSprite;
    NumDisplayButton _numDisplay;

};

#endif // _BUTTON_INCLUDE


