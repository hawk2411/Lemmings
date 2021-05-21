#include "LevelRunner.h"
#include "ShaderManager.h"
#include "PredefinedWordFactory.h"
#include "ButtonFactory.h"
#include "UIAdapter.h"

#include "UserInterface.h"

void UserInterface::init() {
    _selectedButton = -1;

    backgroundTexture.loadFromFile("images/UI/black_frame.png", TEXTURE_PIXEL_FORMAT_RGBA);
    backgroundTexture.setMinFilter(GL_NEAREST);
    backgroundTexture.setMagFilter(GL_NEAREST);

    background = Sprite::createSprite(glm::vec2(UI_WIDTH, UI_HEIGHT), glm::vec2(1., 1.),
                                      &ShaderManager::getInstance().getShaderProgram(), &backgroundTexture);

    jobName = PredefinedWordFactory::instance().createJobWord();

    outWord = PredefinedWordFactory::instance().createInfoWord("OUT");
    numberOutLemmings.init();

    inWord = PredefinedWordFactory::instance().createInfoWord("IN");
    numberInLemmings.init();

    timeWord = PredefinedWordFactory::instance().createInfoWord("TIME");
    time.init();

    selectFrameTexture.loadFromFile("images/UI/white_frame.png", TEXTURE_PIXEL_FORMAT_RGBA);
    selectFrameTexture.setMinFilter(GL_NEAREST);
    selectFrameTexture.setMagFilter(GL_NEAREST);

    _selectFrame = Sprite::createSprite(glm::vec2(17, 25), glm::vec2(17. / 32, 25. / 32),
                                        &ShaderManager::getInstance().getShaderProgram(), &selectFrameTexture);

    for (int i = 0; i < NUM_BUTTONS; ++i) {
        buttons[i] = ButtonFactory::instance().createButton(i);
        buttons[i].setNum(i);
    }

    setPosition(glm::vec2(0, 0));
}

void UserInterface::render() {
    background->render();

    if (jobName) {
        jobName->render();
    }

    outWord->render();
    numberOutLemmings.render();

    inWord->render();
    numberInLemmings.render();

    timeWord->render();
    time.render();

    for (int i = 0; i < NUM_BUTTONS; ++i) {
        buttons[i].render();
    }

    if (_selectedButton != -1) {
        _selectFrame->render();
    }
}

void UserInterface::update(LevelRunner *levelRunner) {
    for (int i = 0; i < 8; ++i) {
        int jobCount = levelRunner->getJobCount(i);
        buttons[i + 2].setNum(jobCount);
    }

    buttons[Button::ButtonNames::MINUS_BUTTON].setNum(levelRunner->getMinReleaseRate());
    buttons[Button::ButtonNames::PLUS_BUTTON].setNum(levelRunner->getReleaseRate());

    numberOutLemmings.displayNum(levelRunner->getNumLemmingsAlive());

    numberInLemmings.displayPercentage(levelRunner->getPercentageSavedLemmings());

    time.displayTime(levelRunner->getRemainingTime());
}

void UserInterface::setPosition(glm::vec2 position) {
    this->_position = position;
    background->setPosition(position);

    jobName->setPosition(position + glm::vec2(0, 1));

    outWord->setPosition(position + glm::vec2(113, 1));
    numberOutLemmings.setPosition(position + glm::vec2(140, 1));

    inWord->setPosition(position + glm::vec2(180, 1));
    numberInLemmings.setPosition(position + glm::vec2(200, 1));

    timeWord->setPosition(position + glm::vec2(247, 1));
    time.setPosition(position + glm::vec2(280, 1));

    for (int i = 0; i < NUM_BUTTONS; ++i) {
        buttons[i].setPosition(position + glm::vec2(16 * i + 1, 13));
    }
}

int UserInterface::getButtonIndexInPos(int posX, int posY, bool isPaused) const {
    for (int i = 0; i < NUM_BUTTONS; ++i) {
        int leftPos = _position.x + 16 * i + 1;
        int rightPos = _position.x + 16 * i + 17;

        if (leftPos <= posX && posX < rightPos && posY >= _position.y + 13) {
            if (i != Button::PAUSE_BUTTON && isPaused) {
                return -1;
            } else {
                return i;
            }
        }
    }

    return -1;
}

void UserInterface::changeSelectedButton(int selectedButton) {
    _selectedButton = selectedButton;

    _selectFrame->setPosition(_position + glm::vec2(16 * selectedButton, 12));
}

void UserInterface::changeDisplayedJob(string lemmingJobName) {
    UIAdapter::changeJobName(jobName.get(), lemmingJobName);
}
