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
    glm::vec2 position;
    std::unique_ptr<Sprite> firstNum;
    std::unique_ptr<Sprite> secondNum;
    std::unique_ptr<Sprite> thirdNum;
    std::unique_ptr<Sprite> percentage;

};

#endif // _PURPLEPERCENTAGEDISPLAY_INCLUDE


