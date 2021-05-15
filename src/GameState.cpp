#include "GameState.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include "common_defs.h"

GameState::GameState() :
        mouseManager(nullptr),
        keyboardManager(nullptr),
        _currentTime(0.0),
        mouseX(0),
        mouseY(0),
        bLeftMouse(false),
        bRightMouse(false) {

}

GameState::~GameState() {

}


void GameState::keyPressed(int key) {
    keyboardManager->keyPressed(key);

}

void GameState::keyReleased(int key) {
}

void GameState::specialKeyPressed(int key) {
    keyboardManager->specialKeyPressed(key);
}

void GameState::specialKeyReleased(int key) {

}

void GameState::mouseMove(int x, int y) {
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    float aspectRatioX = (float(CAMERA_WIDTH) / static_cast<float>(windowWidth));
    float aspectRatioY = (float(CAMERA_HEIGHT) / static_cast<float>(windowHeight));
    mouseX = static_cast<int>(static_cast<float>(x) * aspectRatioX);
    mouseY = static_cast<int>(static_cast<float>(y) * aspectRatioY);

    mouseManager->mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
}

void GameState::mousePress(int button) {
    if (button == GLUT_LEFT_BUTTON) {
        bLeftMouse = true;
        mouseManager->mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
    } else if (button == GLUT_RIGHT_BUTTON) {
        bRightMouse = true;
        mouseManager->mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
    }
}

void GameState::mouseRelease(int button) {
    if (button == GLUT_LEFT_BUTTON) {
        bLeftMouse = false;
        mouseManager->mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
    } else if (button == GLUT_RIGHT_BUTTON) {
        bRightMouse = false;
        mouseManager->mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
    }

}


