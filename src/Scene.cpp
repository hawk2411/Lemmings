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

void Scene::init() {
    Cursor::getInstance().init();

    ParticleSystemManager::getInstance().init();

    if (Game::instance()->isHardMode()) {
        setMaskManager(&HardMaskManager::getInstance());
    } else {
        setMaskManager(&EasyMaskManager::getInstance());
    }

    initMap();
    initUI();

    paused = false;
    speedUp = false;

}

void Scene::update(int deltaTime) {
    update();
    maskManager->update();

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

    LevelRunner::getInstance().update(deltaTime);
    ParticleSystemManager::getInstance().update(deltaTime);
    updateUI();

    if (LevelRunner::getInstance().finished() && ParticleSystemManager::getInstance().finished()) {
        int goalPercentage = LevelRunner::getInstance().getPercentageTotalLemmings();
        int currentPercentage = LevelRunner::getInstance().getPercentageSavedLemmings();

        LevelRunner::getInstance().endMusic();
        StateManager::instance().changeResults(goalPercentage, currentPercentage);
    }

}

void Scene::render() {
    ShaderManager::getInstance().useMaskedShaderProgram();
    map->render(ShaderManager::getInstance().getMaskedShaderProgram(),
                Level::currentLevel().getLevelAttributes()->levelTexture,
                Level::currentLevel().getLevelAttributes()->maskedMap);


    ShaderManager::getInstance().useShaderProgram();
    LevelRunner::getInstance().render();
    ParticleSystemManager::getInstance().render();
    UI::getInstance().render();
    Cursor::getInstance().render();
}

VariableTexture &Scene::getMaskedMap() {
    return Level::currentLevel().getLevelAttributes()->maskedMap;
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

    int levelWidth = Level::currentLevel().getLevelAttributes()->levelTexture.width();
    int levelHeight = Level::currentLevel().getLevelAttributes()->levelTexture.height();
    glm::vec2 normalizedTexCoordStart = glm::vec2(
            Level::currentLevel().getLevelAttributes()->cameraPos.x / levelWidth,
            Level::currentLevel().getLevelAttributes()->cameraPos.y / levelHeight
    );
    glm::vec2 normalizedTexCoordEnd = glm::vec2(
            (Level::currentLevel().getLevelAttributes()->cameraPos.x + LEVEL_WIDTH) / levelWidth,
            (Level::currentLevel().getLevelAttributes()->cameraPos.y + LEVEL_HEIGHT) / levelHeight
    );

    glm::vec2 texCoords[2] = {normalizedTexCoordStart, normalizedTexCoordEnd};
    map = MaskedTexturedQuad::createTexturedQuad(geom, texCoords,
                                                 ShaderManager::getInstance().getMaskedShaderProgram());
}

void Scene::initUI() {
    UI::getInstance().init();
    UI::getInstance().setPosition(glm::vec2(0, LEVEL_HEIGHT - 1));
}

void Scene::updateUI() {
    UI::getInstance().update();
}


void Scene::setMaskManager(MaskManager *maskM) {
    maskManager = maskM;

    maskManager->init();
}

void Scene::eraseMask(int x, int y) {
    maskManager->eraseMask(x, y);
}

void Scene::eraseSpecialMask(int x, int y) {
    maskManager->eraseSpecialMask(x, y);

}

char Scene::getPixel(int x, int y) {
    return maskManager->getPixel(x, y);
}

void Scene::applyMask(int x, int y) {
    maskManager->applyMask(x, y);
}

void Scene::applySpecialMask(int x, int y) {
    maskManager->applySpecialMask(x, y);
}

void Scene::buildStep(glm::vec2 position) {
    for (int i = 0; i < 5; ++i) {
        Utils::changeTexelColor(Level::currentLevel().getLevelAttributes()->levelTexture.getId(), position.x + i,
                                position.y, 120, 77, 0, 255);
        applyMask(position.x + i, position.y);
    }
}

void Scene::onKeyPressed(const SDL_KeyboardEvent &keyboardEvent) {
    if (keyboardEvent.keysym.sym == SDLK_ESCAPE) {
        StateManager::instance().changeMenu();
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
        int lemmingIndex = LevelRunner::getInstance().getLemmingIndexInPos(_mousePosX, _mousePosY);
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


Scene::ScreenMovedArea Scene::getMovedScreenArea() const {
    if (0 <= _mousePosX && _mousePosX < SCROLL_WIDTH && _mousePosY < LEVEL_HEIGHT) {
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

        int selectedLemmingIndex = LevelRunner::getInstance().getLemmingIndexInPos(_mousePosX, _mousePosX);
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
