
#ifndef _PERCENTAGEDISPLAY_INCLUDE
#define _PERCENTAGEDISPLAY_INCLUDE

#include "Sprite.h"

class PercentageDisplay {
public:
    void init(ShaderManager *shaderManager);

    void displayPercentage(int num);

    void render();

    void setPosition(glm::vec2 newPosition);

private:
    glm::vec2 _position;
    std::unique_ptr<Sprite> _firstNum;
    std::unique_ptr<Sprite> _secondNum;
    std::unique_ptr<Sprite> _thirdNum;
    std::unique_ptr<Sprite> _percentage;

};

#endif // _PERCENTAGEDISPLAY_INCLUDE


