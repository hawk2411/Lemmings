#ifndef _UI_INCLUDE
#define _UI_INCLUDE

#include "LevelRunner.h"
#include "Button.h"
#include "Texture.h"
#include "Sprite.h"
#include "Job.h"
#include "NumDisplayGreen.h"
#include "PercentageDisplay.h"
#include "TimeDisplay.h"


class UserInterface {
public:
    explicit UserInterface(ShaderManager *shaderManager);

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

    Button _buttons[NUM_BUTTONS];

    Texture _backgroundTexture;
    std::unique_ptr<Sprite> _background;

    std::unique_ptr<Sprite> _jobName;

    std::unique_ptr<Sprite> _outWord;
    NumDisplayGreen _numberOutLemmings;

    std::unique_ptr<Sprite> _inWord;
    PercentageDisplay _numberInLemmings;

    std::unique_ptr<Sprite> _timeWord;
    TimeDisplay _time;

    int _selectedButton;
    Texture _selectFrameTexture;
    std::unique_ptr<Sprite> _selectFrame;
    ShaderManager* _shaderManager;
};

#endif // _UI_INCLUDE


