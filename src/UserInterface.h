#ifndef _UI_INCLUDE
#define _UI_INCLUDE

#include "Button.h"
#include "Texture.h"
#include "Sprite.h"
#include "Job.h"
#include "NumDisplayGreen.h"
#include "PercentageDisplay.h"
#include "TimeDisplay.h"
#include "LevelRunner.h"

class UserInterface {
public:
    void init();

    void update(LevelRunner *levelRunner);

    void render();

    void setPosition(glm::vec2 position);

    int getButtonIndexInPos(int posX, int posY, bool isPaused) const;

    void changeSelectedButton(int selectedButton);

    void changeDisplayedJob(string lemmingJobName);

    int getSelectedButton()const{return _selectedButton;}

private:
    static const int NUM_BUTTONS = 13;

    glm::vec2 _position;

    Button buttons[NUM_BUTTONS];

    Texture backgroundTexture;
    std::unique_ptr<Sprite> background;

    std::unique_ptr<Sprite> jobName;

    std::unique_ptr<Sprite> outWord;
    NumDisplayGreen numberOutLemmings;

    std::unique_ptr<Sprite> inWord;
    PercentageDisplay numberInLemmings;

    std::unique_ptr<Sprite> timeWord;
    TimeDisplay time;

    int _selectedButton;
    Texture selectFrameTexture;
    std::unique_ptr<Sprite> _selectFrame;
};

#endif // _UI_INCLUDE


