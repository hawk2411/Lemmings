#ifndef _PERCENTAGEDISPLAY_INCLUDE
#define _PERCENTAGEDISPLAY_INCLUDE

#include "Sprite.h"

class PercentageDisplay
{
public:
	void init();
	void displayPercentage(int num);
	void render();
	void setPosition(glm::vec2 newPosition);

private:
	glm::vec2 position;
    std::unique_ptr<Sprite> firstNum;
    std::unique_ptr<Sprite> secondNum;
    std::unique_ptr<Sprite> thirdNum;
    std::unique_ptr<Sprite> percentage;

};

#endif // _PERCENTAGEDISPLAY_INCLUDE


