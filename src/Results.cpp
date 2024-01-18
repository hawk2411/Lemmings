#include "UserEvent.h"
#include "Texture.h"
#include "Game.h"
#include "ShaderManager.h"
#include "LevelRunner.h"

#include "Results.h"
#include "LevelIndex.h"

Results::Results(Game *game, const LevelIndex& levelIndex ) : GameState(game), _levelIndex(levelIndex), _shaderManager(_game->getShaderManager()) {

    _background = Sprite::createSprite(glm::ivec2(CAMERA_WIDTH, CAMERA_HEIGHT), glm::vec2(1, 1),
                                       &_game->getShaderManager()->getShaderProgram(), &_backgroundTexture);
    _continueButton = Sprite::createSprite(glm::ivec2(77, 12), glm::vec2(144. / 256, 25. / 256),
                                           &_game->getShaderManager()->getShaderProgram(),
                                           &Game::spriteSheets().resultsWordSprites);
    _menuButton = Sprite::createSprite(glm::ivec2(77, 12), glm::vec2(144. / 256, 25. / 256),
                                       &_game->getShaderManager()->getShaderProgram(),
                                       &Game::spriteSheets().resultsWordSprites);
    _retryButton = Sprite::createSprite(glm::ivec2(77, 12), glm::vec2(144. / 256, 25. / 256),
                                        &_game->getShaderManager()->getShaderProgram(),
                                        &Game::spriteSheets().resultsWordSprites);
}


void Results::init() {
    _currentTime = 0.0f;
}

void Results::update(int deltaTime) {
    _currentTime += static_cast<float>(deltaTime);
}

void Results::render() {

    _shaderManager->useShaderProgram();

    _background->render();

    _currentPercentageDisplay.render();
    _goalPercentageDisplay.render();

    renderButtons();
}

int Results::getSelectedButton() {
    return _possibleButtons[_selectedButton];
}

void Results::changeSelectedButtonLeft() {
    if(_selectedButton == 0) {
        _selectedButton = _possibleButtons.size() - 1;
    } else{
        --_selectedButton;
    }
}

void Results::changeSelectedButtonRight() {
    if (_selectedButton == _possibleButtons.size() - 1) {
        _selectedButton = 0;
    } else {
        ++_selectedButton;
    }
}

void Results::setPercentages(int goalPercentage, int currentPercentage) {
    _passedLevel = currentPercentage >= goalPercentage;
    string texturePath;
    if (_passedLevel) {
        _possibleButtons = vector<ResultsButtonName>(3);
        _possibleButtons[0] = RETRY;
        _possibleButtons[1] = CONTINUE;
        _possibleButtons[2] = MENU;
        _selectedButton = 1;


        if (currentPercentage == 100) {
            texturePath = "images/results/perfect.png";
        } else if (goalPercentage == currentPercentage) {
            texturePath = "images/results/justInTick.png";
        } else if (currentPercentage < 100) {
            texturePath = "images/results/good.png";
        }
    } else {
        _possibleButtons = vector<ResultsButtonName>(2);
        _possibleButtons[0] = RETRY;
        _possibleButtons[1] = MENU;
        _selectedButton = 0;

        if (currentPercentage == 0) {
            texturePath = "images/results/disaster.png";
        } else if (currentPercentage < goalPercentage) {
            texturePath = "images/results/practice.png";
        }
    }

    _backgroundTexture.loadFromFile(texturePath, PixelFormat::TEXTURE_PIXEL_FORMAT_RGBA);
    _backgroundTexture.setMinFilter(GL_NEAREST);
    _backgroundTexture.setMagFilter(GL_NEAREST);

    _background->setPosition(glm::vec2(0, 0));

    _goalPercentageDisplay.init(_shaderManager);
    _goalPercentageDisplay.displayPercentage(goalPercentage);
    _goalPercentageDisplay.setPosition(glm::vec2(200, 49));

    _currentPercentageDisplay.init(_shaderManager);
    _currentPercentageDisplay.displayPercentage(currentPercentage);
    _currentPercentageDisplay.setPosition(glm::vec2(200, 61));
    initButtons();

}

void Results::initButtons() {

    _continueButton->setNumberAnimations(2);
    _continueButton->addKeyframe(0, glm::vec2(0, 0));
    _continueButton->addKeyframe(1, glm::vec2(0, 25. / 256));
    _continueButton->changeAnimation(0);


    _menuButton->setNumberAnimations(2);
    _menuButton->addKeyframe(0, glm::vec2(0, 50. / 256));
    _menuButton->addKeyframe(1, glm::vec2(0, 75. / 256));
    _menuButton->changeAnimation(0);


    _retryButton->setNumberAnimations(2);
    _retryButton->addKeyframe(0, glm::vec2(0, 100. / 256));
    _retryButton->addKeyframe(1, glm::vec2(0, 125. / 256));
    _retryButton->changeAnimation(0);

    if (_passedLevel) {
        _retryButton->setPosition(glm::vec2(65, 150));
        _continueButton->setPosition(glm::vec2(125, 150));
        _menuButton->setPosition(glm::vec2(215, 150));
    } else {
        _retryButton->setPosition(glm::vec2(100, 150));
        _menuButton->setPosition(glm::vec2(200, 150));
    }
}

void Results::renderButtons() {
    for (int i = 0; i < _possibleButtons.size(); ++i) {
        Sprite *currentButton;
        ResultsButtonName buttonName = _possibleButtons[i];

        switch (buttonName) {
            case RETRY:
                currentButton = _retryButton.get();
                break;
            case CONTINUE:
                currentButton = _continueButton.get();
                break;
            case MENU:
                currentButton = _menuButton.get();
                break;
            default:
                break;
        }

        if (i == _selectedButton) {
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

            switch (selected) {
                case 0: // RETRY
                    UserEvent<CHANGE_TO_INFO, LevelIndex>::sendEvent(new LevelIndex(_levelIndex));
                    break;

                case 1: // CONTINUE

                    switch (_levelIndex.mode) {
                        case LevelModes::Mode::FUN_MODE:
                            if (_levelIndex.levelNo < 4) {
                                UserEvent<CHANGE_TO_INFO, LevelIndex>::sendEvent(
                                        new LevelIndex{ _levelIndex.mode, _levelIndex.levelNo+1});
                                break;
                            }
                            if (_levelIndex.levelNo == 4) {
                                UserEvent<CHANGE_TO_INFO, LevelIndex>::sendEvent(
                                                                  new LevelIndex { _levelIndex.mode, 7});
                                break;
                            }
                            UserEvent<CHANGE_TO_INFO, LevelIndex>::sendEvent(new LevelIndex{LevelModes::Mode::TRICKY_MODE , 1});

                            break;
                        case LevelModes::Mode::TRICKY_MODE:
                            if (_levelIndex.levelNo < 3) {
                                UserEvent<CHANGE_TO_INFO, LevelIndex>::sendEvent(new LevelIndex{_levelIndex.mode, _levelIndex.levelNo});
                            } else {
                                UserEvent<CHANGE_TO_INFO, LevelIndex>::sendEvent( new LevelIndex{LevelModes::Mode::TAXING_MODE, 1});
                            }
                            break;
                        case LevelModes::Mode::TAXING_MODE:
                            UserEvent<CHANGE_TO_MENU>::sendEvent();
                            break;
                    }

                    break;

                case 2: // MENU
                    UserEvent<CHANGE_TO_MENU>::sendEvent();
                    break;
                default:
                    break;
            }
        }
            break;
    }
}

void Results::changeLevel(const LevelIndex &levelIndex) {
    _levelIndex = levelIndex;
}

