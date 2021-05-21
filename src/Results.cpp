#include "Texture.h"
#include "Game.h"
#include "ShaderManager.h"
#include "LevelRunner.h"
#include "StateManager.h"
#include "EventCreator.h"

#include "Results.h"

void Results::init() {
    _currentTime = 0.0f;
}

void Results::update(int deltaTime) {
    _currentTime += deltaTime;
}

void Results::render() {

    ShaderManager::getInstance().useShaderProgram();

    background->render();

    currentPercentageDisplay.render();
    goalPercentageDisplay.render();

    renderButtons();
}

int Results::getSelectedButtonIndex() const {
    return selectedButton;
}

int Results::getSelectedButton() {
    return possibleButtons[selectedButton];
}

void Results::changeSelectedButtonLeft() {
    --selectedButton;
    if (selectedButton < 0) {
        selectedButton = possibleButtons.size() - 1;
    }
}

void Results::changeSelectedButtonRight() {
    ++selectedButton;

    if (selectedButton == possibleButtons.size()) {
        selectedButton = 0;
    }
}

void Results::setPercentages(int goalPercentage, int currentPercentage) {
    passedLevel = currentPercentage >= goalPercentage;
    string texturePath = "";
    if (passedLevel) {
        possibleButtons = vector<ResultsButtonName>(3);
        possibleButtons[0] = RETRY;
        possibleButtons[1] = CONTINUE;
        possibleButtons[2] = MENU;
        selectedButton = 1;


        if (currentPercentage == 100) {
            texturePath = "images/results/perfect.png";
        } else if (goalPercentage == currentPercentage) {
            texturePath = "images/results/justInTick.png";
        } else if (currentPercentage < 100) {
            texturePath = "images/results/good.png";
        }
    } else {
        possibleButtons = vector<ResultsButtonName>(2);
        possibleButtons[0] = RETRY;
        possibleButtons[1] = MENU;
        selectedButton = 0;

        if (currentPercentage == 0) {
            texturePath = "images/results/disaster.png";
        } else if (currentPercentage < goalPercentage) {
            texturePath = "images/results/practice.png";
        }
    }

    backgroundTexture.loadFromFile(texturePath, TEXTURE_PIXEL_FORMAT_RGBA);
    backgroundTexture.setMinFilter(GL_NEAREST);
    backgroundTexture.setMagFilter(GL_NEAREST);

    background = Sprite::createSprite(glm::ivec2(CAMERA_WIDTH, CAMERA_HEIGHT), glm::vec2(1, 1),
                                      &ShaderManager::getInstance().getShaderProgram(), &backgroundTexture);
    background->setPosition(glm::vec2(0, 0));

    goalPercentageDisplay.init();
    goalPercentageDisplay.displayPercentage(goalPercentage);
    goalPercentageDisplay.setPosition(glm::vec2(200, 49));

    currentPercentageDisplay.init();
    currentPercentageDisplay.displayPercentage(currentPercentage);
    currentPercentageDisplay.setPosition(glm::vec2(200, 61));
    initButtons();

}

void Results::initButtons() {
    continueButton = Sprite::createSprite(glm::ivec2(77, 12), glm::vec2(144. / 256, 25. / 256),
                                          &ShaderManager::getInstance().getShaderProgram(),
                                          &Game::spriteSheets().resultsWordSprites);
    continueButton->setNumberAnimations(2);
    continueButton->addKeyframe(0, glm::vec2(0, 0));
    continueButton->addKeyframe(1, glm::vec2(0, 25. / 256));
    continueButton->changeAnimation(0);

    menuButton = Sprite::createSprite(glm::ivec2(77, 12), glm::vec2(144. / 256, 25. / 256),
                                      &ShaderManager::getInstance().getShaderProgram(),
                                      &Game::spriteSheets().resultsWordSprites);
    menuButton->setNumberAnimations(2);
    menuButton->addKeyframe(0, glm::vec2(0, 50. / 256));
    menuButton->addKeyframe(1, glm::vec2(0, 75. / 256));
    menuButton->changeAnimation(0);

    retryButton = Sprite::createSprite(glm::ivec2(77, 12), glm::vec2(144. / 256, 25. / 256),
                                       &ShaderManager::getInstance().getShaderProgram(),
                                       &Game::spriteSheets().resultsWordSprites);
    retryButton->setNumberAnimations(2);
    retryButton->addKeyframe(0, glm::vec2(0, 100. / 256));
    retryButton->addKeyframe(1, glm::vec2(0, 125. / 256));
    retryButton->changeAnimation(0);

    if (passedLevel) {
        retryButton->setPosition(glm::vec2(65, 150));
        continueButton->setPosition(glm::vec2(125, 150));
        menuButton->setPosition(glm::vec2(215, 150));
    } else {
        retryButton->setPosition(glm::vec2(100, 150));
        menuButton->setPosition(glm::vec2(200, 150));
    }
}

void Results::renderButtons() {
    for (int i = 0; i < possibleButtons.size(); ++i) {
        Sprite *currentButton;
        ResultsButtonName buttonName = possibleButtons[i];

        switch (buttonName) {
            case RETRY:
                currentButton = retryButton.get();
                break;
            case CONTINUE:
                currentButton = continueButton.get();
                break;
            case MENU:
                currentButton = menuButton.get();
                break;
            default:
                break;
        }

        if (i == selectedButton) {
            currentButton->changeAnimation(1);
        } else {
            currentButton->changeAnimation(0);
        }
        currentButton->render();
    }
}

void Results::mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton) {

}

void Results::onKeyPressed(const SDL_KeyboardEvent &keyboardEvent) {
    switch (keyboardEvent.keysym.sym) {
        case SDLK_RIGHT:
            changeSelectedButtonRight();
            break;

        case SDLK_LEFT:
            changeSelectedButtonLeft();
            break;
        case SDLK_RETURN: {
            int selected = getSelectedButton();
            int currentLevel = _level;
            //int currentMode = LevelRunner::getInstance().getActualMode();

            switch (selected) {
                case 0: // RETRY
                    // TODO
                    //StateManager::instance().changeInfo(currentMode, currentLevel);
                    EventCreator::sendSimpleUserEvent(CHANGE_TO_INFO, new int(LevelModes::convertToInt(_levelMode)), new int(_level));
                    break;

                case 1: // CONTINUE

                    switch (_levelMode) {
                        case LevelModes::Mode::FUN_MODE:
                            if (currentLevel < 4) {
                                EventCreator::sendSimpleUserEvent(CHANGE_TO_INFO, new int(LevelModes::convertToInt(_levelMode)), new int(_level+1));
                            } else if (currentLevel == 4) {
                                EventCreator::sendSimpleUserEvent(CHANGE_TO_INFO, new int(LevelModes::convertToInt(_levelMode)), new int(7));
                            } else {
                                EventCreator::sendSimpleUserEvent(CHANGE_TO_INFO, new int(LevelModes::convertToInt(LevelModes::Mode::TRICKY_MODE)), new int(1));
                            }
                            break;
                        case LevelModes::Mode::TRICKY_MODE:
                            if (currentLevel < 3) {
                                EventCreator::sendSimpleUserEvent(CHANGE_TO_INFO, new int(LevelModes::convertToInt(_levelMode)), new int(_level+1));
                            } else {
                                EventCreator::sendSimpleUserEvent(CHANGE_TO_INFO, new int(LevelModes::convertToInt(LevelModes::Mode::TAXING_MODE)), new int(1));
                            }
                            break;
                        case LevelModes::Mode::TAXING_MODE:
                            EventCreator::sendSimpleUserEvent(CHANGE_TO_MENU);
                            break;
                    }

                    break;

                case 2: // MENU
                    EventCreator::sendSimpleUserEvent(CHANGE_TO_MENU);
                    break;
            }
        }
        break;
    }
}
