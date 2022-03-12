#include "ShaderManager.h"
#include "PredefinedWordFactory.h"
#include "ButtonFactory.h"
#include "UIAdapter.h"

#include "UserInterface.h"

UserInterface::UserInterface(ShaderManager *shaderManager):
            _shaderManager(shaderManager), _position(0,0), _selectedButton(0) {

    _backgroundTexture.loadFromFile("images/UI/black_frame.png", TEXTURE_PIXEL_FORMAT_RGBA);
    _backgroundTexture.setMinFilter(GL_NEAREST);
    _backgroundTexture.setMagFilter(GL_NEAREST);

    _background = Sprite::createSprite(glm::vec2(UI_WIDTH, UI_HEIGHT), glm::vec2(1., 1.),
                                       &_shaderManager->getShaderProgram(), &_backgroundTexture);
    _jobName = PredefinedWordFactory::createJobWord(&_shaderManager->getShaderProgram());

    _outWord = PredefinedWordFactory::createInfoWord("OUT", &_shaderManager->getShaderProgram());

    _inWord = PredefinedWordFactory::createInfoWord("IN", &_shaderManager->getShaderProgram());

    _timeWord = PredefinedWordFactory::createInfoWord("TIME", &_shaderManager->getShaderProgram());
    _selectFrameTexture.loadFromFile("images/UI/white_frame.png", TEXTURE_PIXEL_FORMAT_RGBA);
    _selectFrameTexture.setMinFilter(GL_NEAREST);
    _selectFrameTexture.setMagFilter(GL_NEAREST);

    _selectFrame = Sprite::createSprite(glm::vec2(17, 25), glm::vec2(17. / 32, 25. / 32),
                                        &_shaderManager->getShaderProgram(), &_selectFrameTexture);

    for (int i = 0; i < NUM_BUTTONS; ++i) {
        _buttons[i] = ButtonFactory::createButton(i, _shaderManager);
        _buttons[i].setNum(i);
    }

}

void UserInterface::init() {
    _selectedButton = -1;
    _numberOutLemmings.init(_shaderManager);
    _numberInLemmings.init(_shaderManager);
    _time.init(_shaderManager);
    setPosition(glm::vec2(0, 0));
}

void UserInterface::render() {
    _background->render();

    if (_jobName) {
        _jobName->render();
    }

    _outWord->render();
    _numberOutLemmings.render();

    _inWord->render();
    _numberInLemmings.render();

    _timeWord->render();
    _time.render();

    for (auto & _button : _buttons) {
        _button.render();
    }

    if (_selectedButton != -1) {
        _selectFrame->render();
    }
}

void UserInterface::update(LevelRunner *levelRunner) {
    for (int i = 0; i < 8; ++i) {
        int jobCount = levelRunner->getJobCount(i);
        _buttons[i + 2].setNum(jobCount);
    }

    _buttons[Button::ButtonNames::MINUS_BUTTON].setNum(levelRunner->getMinReleaseRate());
    _buttons[Button::ButtonNames::PLUS_BUTTON].setNum(levelRunner->getReleaseRate());

    _numberOutLemmings.displayNum(levelRunner->getNumLemmingsAlive());

    _numberInLemmings.displayPercentage(levelRunner->getPercentageSavedLemmings());

    _time.displayTime(levelRunner->getRemainingTime());
}

void UserInterface::setPosition(glm::vec2 position) {
    this->_position = position;
    _background->setPosition(position);

    _jobName->setPosition(position + glm::vec2(0, 1));

    _outWord->setPosition(position + glm::vec2(113, 1));
    _numberOutLemmings.setPosition(position + glm::vec2(140, 1));

    _inWord->setPosition(position + glm::vec2(180, 1));
    _numberInLemmings.setPosition(position + glm::vec2(200, 1));

    _timeWord->setPosition(position + glm::vec2(247, 1));
    _time.setPosition(position + glm::vec2(280, 1));

    for (int i = 0; i < NUM_BUTTONS; ++i) {
        _buttons[i].setPosition(position + glm::vec2(16 * i + 1, 13));
    }
}

int UserInterface::getButtonIndexInPos(int posX, int posY, bool isPaused) const {
    for (int i = 0; i < NUM_BUTTONS; ++i) {
        int leftPos = static_cast<int>(_position.x) + 16 * i + 1;
        int rightPos = static_cast<int>(_position.x) + 16 * i + 17;

        if (leftPos <= posX && posX < rightPos && posY >= static_cast<int>(_position.y) + 13) {
            return (i != Button::PAUSE_BUTTON && isPaused) ? -1 : i;
        }
    }
    return -1;
}

void UserInterface::changeSelectedButton(int selectedButton) {
    _selectedButton = selectedButton;

    _selectFrame->setPosition(_position + glm::vec2(16 * selectedButton, 12));
}

void UserInterface::changeDisplayedJob(const string& lemmingJobName) {
    UIAdapter::changeJobName(_jobName.get(), lemmingJobName);
}


