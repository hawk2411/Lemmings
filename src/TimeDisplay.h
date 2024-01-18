#ifndef _TIMEDISPLAY_INCLUDE
#define _TIMEDISPLAY_INCLUDE

#include "Sprite.h"
#include "ShaderManager.h"

class TimeDisplay {
public:
    void init(ShaderManager *shaderManager);

    void displayTime(int time);

    void render();

    void setPosition(glm::vec2 position);

private:
    glm::vec2 _position;
    std::unique_ptr<Sprite> _minutes;
    std::unique_ptr<Sprite> _firstDigitSeconds;
    std::unique_ptr<Sprite> _secondDigitSeconds;
    std::unique_ptr<Sprite> _hyphen;

};

#endif // _TIMEDISPLAY_INCLUDE


