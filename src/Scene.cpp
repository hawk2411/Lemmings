#include <iostream>
#include <algorithm>
#include "Game.h"
#include "Cursor.h"
#include "Utils.h"
#include "HardMaskManager.h"
#include "EasyMaskManager.h"
#include "EventCreator.h"

#include "Scene.h"
#include "LevelIndex.h"

Scene::Scene(Game *game, SoundManager *soundManager, const LevelIndex &levelIndex)
        : GameState(game), _scroller(false), _shaderManager(_game->getShaderManager()), _ui(_game->getShaderManager()),
          _cursor(_game->getShaderManager()) {

    _levelRunner = std::make_unique<LevelRunner>(soundManager, _game->getShaderManager(), levelIndex);

    _maskManagers.insert(std::make_pair(Difficulties::Mode::Easy, std::unique_ptr<IMaskManager>(
            new EasyMaskManager(_levelRunner->getLevelAttributes()))));

    _maskManagers.insert(std::make_pair(Difficulties::Mode::Hard, std::unique_ptr<IMaskManager>(
            new HardMaskManager(_levelRunner->getLevelAttributes()))));

    _currentDifficultyMode = game->getDifficultyMode();
}

void Scene::init() {
    _cursor.init();

    _particleSystemManager.init();

    initMap();
    initUI();

    paused = false;
    speedUp = false;

}

void Scene::update(int deltaTime) {
    update();
    _maskManagers[_currentDifficultyMode].get()->update(deltaTime);

    if (_scroller.isScrolled()) {
        initMap();
        _scroller.setScroll(false);
    }

    if (paused) {
        return;
    }

    if (speedUp) {
        deltaTime = 4 * deltaTime;
    }

    _levelRunner->update(deltaTime, _maskManagers[_currentDifficultyMode].get());
    _particleSystemManager.update(deltaTime);
    updateUI();

    if (_levelRunner->finished() && _particleSystemManager.finished()) {
        auto *resultStatistic = new ResultStatistic{_levelRunner->getPercentageTotalLemmings(),
                                                    _levelRunner->getPercentageSavedLemmings()};
        auto *levelIndex = new LevelIndex{_levelRunner->getActualMode(), _levelRunner->getActualLevel()};
        _levelRunner->endMusic();

        EventCreator::sendSimpleUserEvent(CHANGE_TO_RESULT, resultStatistic, levelIndex);
    }

}

void Scene::render() {
    _shaderManager->useMaskedShaderProgram();
    _map->render(_shaderManager->getMaskedShaderProgram(),
                 _levelRunner->getLevelAttributes()->levelTexture,
                 _levelRunner->getLevelAttributes()->maskedMap);


    _shaderManager->useShaderProgram();
    _levelRunner->render();
    _particleSystemManager.render(_levelRunner->getLevelAttributes()->cameraPos);
    _ui.render();
    _cursor.render();
}

VariableTexture &Scene::getMaskedMap() {
    return _levelRunner->getLevelAttributes()->maskedMap;
}

void Scene::changePauseStatus() {
    paused = !paused;
}

void Scene::changeSpeedUpStatus() {
    speedUp = !speedUp;
}

bool Scene::isPaused() const {
    return paused;
}

bool Scene::isSpeedUp() const {
    return speedUp;
}


void Scene::initMap() {
    glm::vec2 geom[2] = {glm::vec2(0.f, 0.f), glm::vec2(float(LEVEL_WIDTH), float(LEVEL_HEIGHT))};

    int levelWidth = _levelRunner->getLevelAttributes()->levelTexture.width();
    int levelHeight = _levelRunner->getLevelAttributes()->levelTexture.height();
    glm::vec2 normalizedTexCoordStart = glm::vec2(
            _levelRunner->getLevelAttributes()->cameraPos.x / static_cast<float>(levelWidth),
            _levelRunner->getLevelAttributes()->cameraPos.y / static_cast<float>(levelHeight)
    );
    glm::vec2 normalizedTexCoordEnd = glm::vec2(
            (_levelRunner->getLevelAttributes()->cameraPos.x + LEVEL_WIDTH) / static_cast<float>(levelWidth),
            (_levelRunner->getLevelAttributes()->cameraPos.y + LEVEL_HEIGHT) / static_cast<float>(levelHeight)
    );

    glm::vec2 texCoords[2] = {normalizedTexCoordStart, normalizedTexCoordEnd};
    _map = MaskedTexturedQuad::createTexturedQuad(geom, texCoords,
                                                  _shaderManager->getMaskedShaderProgram());
}

void Scene::initUI() {
    _ui.init();
    _ui.setPosition(glm::vec2(0, LEVEL_HEIGHT - 1));
}

void Scene::updateUI() {
    _ui.update(_levelRunner.get());
}

void Scene::update() {
    updateCursorPosition();

    if (screenMovedArea == ScreenMovedArea::SCROLL_AREA_LEFT) {
        _scroller.scrollLeft(_levelRunner->getLevelAttributes()->cameraPos,
                             static_cast<int>(_levelRunner->getLevelAttributes()->levelSize.x));
        _cursor.setScrollLeftCursor();
        return;
    }
    if (screenMovedArea == ScreenMovedArea::SCROLL_AREA_RIGHT) {
        _scroller.scrollRight(_levelRunner->getLevelAttributes()->cameraPos,
                              static_cast<int>(_levelRunner->getLevelAttributes()->levelSize.x));
        _cursor.setScrollRightCursor();
        return;
    }
    if (screenMovedArea == ScreenMovedArea::LEVEL) {
        int lemmingIndex = _levelRunner->getLemmingIndexInPos(posX, posY);
        _ui.changeDisplayedJob(_levelRunner->getLemmingJobNameIndex(lemmingIndex));

        if (lemmingIndex != -1) {
            _cursor.setFocusCursor();
        } else {
            _cursor.setCrossCursor();
        }
        return;
    }
    _cursor.setCrossCursor();

}

void Scene::eraseMask(int x, int y) {
    _maskManagers[_currentDifficultyMode]->eraseMask(x, y, 0);
}

void Scene::eraseSpecialMask(int x, int y) {
    _maskManagers[_currentDifficultyMode]->eraseSpecialMask(x, y);

}

char Scene::getPixel(int x, int y) {
    return _maskManagers[_currentDifficultyMode]->getPixel(x, y);
}

void Scene::applyMask(int x, int y) {
    _maskManagers[_currentDifficultyMode]->applyMask(x, y);
}

void Scene::applySpecialMask(int x, int y) {
    _maskManagers[_currentDifficultyMode]->applySpecialMask(x, y);
}

void Scene::buildStep(glm::vec2 position) {
    for (int i = 0; i < 5; ++i) {
        Utils::changeTexelColor(_levelRunner->getLevelAttributes()->levelTexture.getId(), position.x + i,
                                position.y, 120, 77, 0, 255);
        applyMask(position.x + i, position.y);
    }
}

void Scene::onKeyPressed(const SDL_KeyboardEvent &keyboardEvent) {
    if (keyboardEvent.keysym.sym == SDLK_ESCAPE) {
        _game->getStateManager()->changeMenu();
    }

}

void Scene::mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton) {
    posX = mouseX;
    posY = mouseY;

    ScreenClickedArea screenClickedArea = getClickedScreenArea(mouseX, mouseY);
    screenMovedArea = getMovedScreenArea(mouseX, mouseY);
    if (screenMovedArea == SCROLL_AREA_LEFT) {
        int a = 2;
    }

    switch (mouseState) {

        case LEFT_MOUSE_PRESSED:
            if (!bLeftButton) {
                mouseState = MouseStates::NONE;

            }
            break;

        case RIGHT_MOUSE_PRESSED:

            if (!bRightButton) {
                mouseState = MouseStates::NONE;
            }
            break;

        case MouseStates::NONE:

            if (bLeftButton) {
                mouseState = LEFT_MOUSE_PRESSED;

                if (screenClickedArea == ScreenClickedArea::UI) {
                    leftClickOnUI(mouseX, mouseY);
                } else if (screenClickedArea == ScreenClickedArea::MAP) {
                    leftClickOnMap(mouseX, mouseY);
                } else if (screenClickedArea == ScreenClickedArea::INFO) {

                }

            } else if (bRightButton) {
                mouseState = RIGHT_MOUSE_PRESSED;

                if (screenClickedArea == ScreenClickedArea::UI) {
                } else if (screenClickedArea == ScreenClickedArea::MAP) {

                }

            } else {

            }

            break;
    }
}

Scene::ScreenClickedArea Scene::getClickedScreenArea(int mouseX, int mouseY) {
    if (
            0 <= mouseX
            && mouseX < LEVEL_WIDTH
            && 0 <= mouseY
            && mouseY < LEVEL_HEIGHT
            ) {
        return ScreenClickedArea::MAP;
    } else if (
            0 <= mouseX
            && mouseX < UI_WIDTH
            && LEVEL_HEIGHT <= mouseY
            && mouseY < LEVEL_HEIGHT + UI_HEIGHT
            ) {
        return ScreenClickedArea::UI;
    }
    throw std::runtime_error("Scene::getClickedScreenArea unknown behavior.");
}


Scene::ScreenMovedArea Scene::getMovedScreenArea(int mouseX, int mouseY) {
    if (0 <= mouseX && mouseX < SCROLL_WIDTH && mouseY < LEVEL_HEIGHT) {
        return ScreenMovedArea::SCROLL_AREA_LEFT;
    } else if (LEVEL_WIDTH - SCROLL_WIDTH <= mouseX && mouseX < LEVEL_WIDTH && mouseY < LEVEL_HEIGHT) {
        return ScreenMovedArea::SCROLL_AREA_RIGHT;
    } else if (SCROLL_WIDTH <= mouseX && mouseX < LEVEL_WIDTH - SCROLL_WIDTH && mouseY < LEVEL_HEIGHT) {
        return ScreenMovedArea::LEVEL;
    } else {
        return ScreenMovedArea::NONE_AREA;
    }
}


void Scene::leftClickOnUI(int posX, int posY) {
    int clickedButtonIndex = _ui.getButtonIndexInPos(posX, posY, isPaused());
    _ui.changeSelectedButton(clickedButtonIndex);

    activateButton(clickedButtonIndex);
}

void Scene::leftClickOnMap(int posX, int posY) {

    if (_jobAssigner.hasJobToAssign()) {

        int selectedLemmingIndex = _levelRunner->getLemmingIndexInPos(posX, posY);
        //_jobAssigner.assignJobLemming(selectedLemmingIndex);
        if (_levelRunner->assignJob(selectedLemmingIndex, _jobAssigner.getJobToAssign())) {
            auto jobName = _jobAssigner.getLastOfferedJob();
            int jobIndex = _jobAssigner.jobNameToIndex(jobName);
            _levelRunner->decreaseJobCount(jobIndex);
            if (_levelRunner->getJobCount(jobIndex) > 0) {
                _jobAssigner.offerJob(jobName);
            } else {
                _jobAssigner.setLastOfferedJob(JobAssigner::NONE);
            }
            //_jobAssigner.assignJobLemming(selectedLemmingIndex);
        }
    }
}

void Scene::updateCursorPosition() {
    glm::vec2 cursorPosition = glm::vec2(posX, posY) - glm::vec2(6, 6);

    if (cursorPosition.x < 0) {
        cursorPosition.x = 0;
    } else if (cursorPosition.x >= CAMERA_WIDTH - 12) {
        cursorPosition.x = CAMERA_WIDTH - 13;
    }

    if (cursorPosition.y < 0) {
        cursorPosition.y = 0;
    } else if (cursorPosition.y >= CAMERA_HEIGHT - 12) {
        cursorPosition.y = CAMERA_HEIGHT - 13;
    }

    _cursor.setPosition(cursorPosition);

}

void Scene::changeLevel(const LevelIndex &levelIndex) {
    // TODO why is nothing happen here?
    if (_levelRunner->getActualMode() != levelIndex.mode || _levelRunner->getActualLevel() != levelIndex.levelNo) {
        _levelRunner->changeLevel(levelIndex);
        _maskManagers[_currentDifficultyMode]->changeLevel(_levelRunner->getLevelAttributes());
    }
}


void Scene::activateButton(int buttonIndex) {
    _jobAssigner.deleteJobToAssign();

    switch (buttonIndex) {
        case Button::MINUS_BUTTON:
            if (_levelRunner->getLevelAttributes()->releaseRate) {
                _levelRunner->decreaseReleaseRate();
            }
            break;
        case Button::PLUS_BUTTON:
            if (_levelRunner->getLevelAttributes()->releaseRate) {
                _levelRunner->increaseReleaseRate();
            }
            break;
        case Button::CLIMBER_BUTTON:
            if (getSelectedButtonJobCount() > 0) {
                _jobAssigner.offerJob(JobAssigner::JobNames::CLIMBER);
            }
            break;
        case Button::FLOATER_BUTTON:
            if (getSelectedButtonJobCount() > 0) {
                _jobAssigner.offerJob(JobAssigner::JobNames::FLOATER);
            }
            break;
        case Button::EXPLODER_BUTTON:
            if (getSelectedButtonJobCount() > 0) {
                _jobAssigner.offerJob(JobAssigner::JobNames::BOMBER);
            }
            break;
        case Button::BLOCKER_BUTTON:
            if (getSelectedButtonJobCount() > 0) {
                _jobAssigner.offerJob(JobAssigner::JobNames::BLOCKER);
            }
            break;
        case Button::BUILDER_BUTTON:
            if (getSelectedButtonJobCount() > 0) {
                _jobAssigner.offerJob(JobAssigner::JobNames::BUILDER);
            }
            break;
        case Button::BASHER_BUTTON:
            if (getSelectedButtonJobCount() > 0) {
                _jobAssigner.offerJob(JobAssigner::JobNames::BASHER);
            }
            break;
        case Button::MINER_BUTTON:
            if (getSelectedButtonJobCount() > 0) {
                _jobAssigner.offerJob(JobAssigner::JobNames::MINER);
            }
            break;
        case Button::DIGGER_BUTTON:
            if (getSelectedButtonJobCount() > 0) {
                _jobAssigner.offerJob(JobAssigner::JobNames::DIGGER);
            }
            break;
        case Button::PAUSE_BUTTON:
            changePauseStatus();
            if (!isPaused()) {
                _ui.changeSelectedButton(-1);
            }
            break;
        case Button::NUKE_BUTTON:
            _levelRunner->apocalypse();
            break;
        case Button::SPEED_BUTTON:
            changeSpeedUpStatus();
            if (!isSpeedUp()) {
                _ui.changeSelectedButton(-1);
            }
            break;
        default:
            break;
    }

}

int Scene::getSelectedButtonJobCount() {
    return _levelRunner->getLevelAttributes()->lemmingsProJob[_ui.getSelectedButton() - 2];
}

void Scene::createNewParticleSystem(glm::vec2 vec) {
    _particleSystemManager.createNewParticleSystem(&_shaderManager->getMaskedShaderProgram(), vec);
}
