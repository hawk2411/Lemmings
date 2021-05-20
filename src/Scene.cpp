#include <iostream>
#include <cmath>
#include <ctime>
#include <algorithm>
#include "Game.h"
#include "Scene.h"
#include "ShaderManager.h"
#include "Scroller.h"
#include "Cursor.h"
#include "ParticleSystemManager.h"
#include "StateManager.h"
#include "Utils.h"
#include "HardMaskManager.h"
#include "EasyMaskManager.h"
#include "LevelRunner.h"
#include "JobAssigner.h"
#include "UIAdapter.h"

Scene::Scene(Game *game, SoundManager *soundManager) : GameState(game) {
    _levelRunner = std::make_unique<LevelRunner>(soundManager, LevelModes::Mode::FUN_MODE, 0);
    _maskManagers.insert(std::make_pair(Difficulties::Mode::Easy, std::unique_ptr<IMaskManager>(new EasyMaskManager(_levelRunner->getLevelAttributes()))));
    _maskManagers.insert(std::make_pair(Difficulties::Mode::Hard, std::unique_ptr<IMaskManager>(new HardMaskManager(_levelRunner->getLevelAttributes()))));
    _currentDifficultyMode = game->getDifficultyMode();
}
void Scene::init() {
    Cursor::getInstance().init();

    ParticleSystemManager::getInstance().init();
    _currentDifficultyMode = _game->getDifficultyMode();

    initMap();
    initUI();

    paused = false;
    speedUp = false;

}

void Scene::update(int deltaTime) {
    update();
    _maskManagers[_currentDifficultyMode].get()->update();

    if (Scroller::getInstance().isScrolled()) {
        initMap();
        Scroller::getInstance().iScroll();
    }

    if (paused) {
        return;
    }

    if (speedUp) {
        deltaTime = 4 * deltaTime;
    }

    _levelRunner->update(deltaTime, _maskManagers[_currentDifficultyMode].get());
    ParticleSystemManager::getInstance().update(deltaTime);
    updateUI();

    if (_levelRunner->finished() && ParticleSystemManager::getInstance().finished()) {
        int goalPercentage = _levelRunner->getPercentageTotalLemmings();
        int currentPercentage = _levelRunner->getPercentageSavedLemmings();

        _levelRunner->endMusic();
        StateManager::instance().changeResults(goalPercentage, currentPercentage);
    }

}

void Scene::render() {
    ShaderManager::getInstance().useMaskedShaderProgram();
    _map->render(ShaderManager::getInstance().getMaskedShaderProgram(),
                 _levelRunner->getLevelAttributes()->levelTexture,
                 _levelRunner->getLevelAttributes()->maskedMap);


    ShaderManager::getInstance().useShaderProgram();
    _levelRunner->render();
    ParticleSystemManager::getInstance().render();
    UI::getInstance().render();
    Cursor::getInstance().render();
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
    int levelHeight =_levelRunner->getLevelAttributes()->levelTexture.height();
    glm::vec2 normalizedTexCoordStart = glm::vec2(
            _levelRunner->getLevelAttributes()->cameraPos.x / levelWidth,
            _levelRunner->getLevelAttributes()->cameraPos.y / levelHeight
    );
    glm::vec2 normalizedTexCoordEnd = glm::vec2(
            (_levelRunner->getLevelAttributes()->cameraPos.x + LEVEL_WIDTH) / levelWidth,
            (_levelRunner->getLevelAttributes()->cameraPos.y + LEVEL_HEIGHT) / levelHeight
    );

    glm::vec2 texCoords[2] = {normalizedTexCoordStart, normalizedTexCoordEnd};
    _map = MaskedTexturedQuad::createTexturedQuad(geom, texCoords,
                                                  ShaderManager::getInstance().getMaskedShaderProgram());
}

void Scene::initUI() {
    UI::getInstance().init();
    UI::getInstance().setPosition(glm::vec2(0, LEVEL_HEIGHT - 1));
}

void Scene::updateUI() {
    UI::getInstance().update();
}

void Scene::eraseMask(int x, int y) {
    _maskManagers[_currentDifficultyMode]->eraseMask(x, y);
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

void Scene::update() {
    updateCursorPosition();

    if (screenMovedArea == ScreenMovedArea::SCROLL_AREA_LEFT) {
        Scroller::getInstance().scrollLeft();
        Cursor::getInstance().setScrollLeftCursor();
    } else if (screenMovedArea == ScreenMovedArea::SCROLL_AREA_RIGHT) {
        Scroller::getInstance().scrollRight();
        Cursor::getInstance().setScrollRightCursor();
    } else if (screenMovedArea == ScreenMovedArea::LEVEL) {
        int lemmingIndex = _levelRunner->getLemmingIndexInPos(posX, posY);
        UIAdapter::getInstance().changeFocusedLemming(lemmingIndex);

        if (lemmingIndex != -1) {
            Cursor::getInstance().setFocusCursor();
        } else {
            Cursor::getInstance().setCrossCursor();
        }

    } else {
        Cursor::getInstance().setCrossCursor();
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
    int clickedButtonIndex = UI::getInstance().getButtonIndexInPos(posX, posY);
    UIAdapter::getInstance().changeSelectedButton(clickedButtonIndex);
}

void Scene::leftClickOnMap(int posX, int posY) {

    if (JobAssigner::getInstance().hasJobToAssign()) {

        int selectedLemmingIndex = _levelRunner->getLemmingIndexInPos(posX, posY);
        JobAssigner::getInstance().assigJobLemming(selectedLemmingIndex);
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

    Cursor::getInstance().setPosition(cursorPosition);

}

void Scene::setLevel(LevelModes::Mode mode, int i) {

}


