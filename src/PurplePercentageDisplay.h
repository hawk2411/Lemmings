#ifndef _PURPLEPERCENTAGEDISPLAY_INCLUDE
#define _PURPLEPERCENTAGEDISPLAY_INCLUDE

#include "Sprite.h"
#include "ShaderManager.h"

class PurplePercentageDisplay {
public:
    void init(ShaderManager *shaderManager);

    void displayPercentage(int num);

    void render();

    void setPosition(glm::vec2 position);

private:
    glm::vec2 _position;
    std::unique_ptr<Sprite> _firstNum;
    std::unique_ptr<Sprite> _secondNum;
    std::unique_ptr<Sprite> _thirdNum;
    std::unique_ptr<Sprite> _percentage;

};

#endif // _PURPLEPERCENTAGEDISPLAY_INCLUDE


