#include "SceneMouseManager.h"
#include "LevelManager.h"
#include "Cursor.h"
#include "Scroller.h"
#include "UI.h"
#include "UIAdapter.h"
#include "JobAssigner.h"


void SceneMouseManager::mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton) {
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

void SceneMouseManager::update() {
    updateCursorPosition();

    if (screenMovedArea == ScreenMovedArea::SCROLL_AREA_LEFT) {
        Scroller::getInstance().scrollLeft();
        Cursor::getInstance().setScrollLeftCursor();
    } else if (screenMovedArea == ScreenMovedArea::SCROLL_AREA_RIGHT) {
        Scroller::getInstance().scrollRight();
        Cursor::getInstance().setScrollRightCursor();
    } else if (screenMovedArea == ScreenMovedArea::LEVEL) {
        int lemmingIndex = LevelManager::getInstance().getLemmingIndexInPos(posX, posY);
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

SceneMouseManager::ScreenClickedArea SceneMouseManager::getClickedScreenArea(int mouseX, int mouseY) {
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
    throw std::runtime_error("SceneMouseManager::getClickedScreenArea unknown behavior.");
}

SceneMouseManager::ScreenMovedArea SceneMouseManager::getMovedScreenArea(int mouseX, int mouseY) {
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


void SceneMouseManager::leftClickOnUI(int posX, int posY) {
    int clickedButtonIndex = UI::getInstance().getButtonIndexInPos(posX, posY);
    UIAdapter::getInstance().changeSelectedButton(clickedButtonIndex);
}


void SceneMouseManager::leftClickOnMap(int posX, int posY) {

    if (JobAssigner::getInstance().hasJobToAssign()) {

        int selectedLemmingIndex = LevelManager::getInstance().getLemmingIndexInPos(posX, posY);
        JobAssigner::getInstance().assigJobLemming(selectedLemmingIndex);
    }
}

void SceneMouseManager::updateCursorPosition() {
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