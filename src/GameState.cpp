#include <GL/glew.h>
#include <GL/glut.h>
#include "common_defs.h"

#include "GameState.h"

GameState::GameState() :
        _currentTime(0.0),
        mouseX(0),
        mouseY(0),
        bLeftMouse(false),
        bRightMouse(false) {

}

GameState::~GameState() {

}


void GameState::mouseMove(int x, int y) {
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    float aspectRatioX = (float(CAMERA_WIDTH) / static_cast<float>(windowWidth));
    float aspectRatioY = (float(CAMERA_HEIGHT) / static_cast<float>(windowHeight));
    mouseX = static_cast<int>(static_cast<float>(x) * aspectRatioX);
    mouseY = static_cast<int>(static_cast<float>(y) * aspectRatioY);

    mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
}

void GameState::mousePress(int button) {
    if (button == GLUT_LEFT_BUTTON) {
        bLeftMouse = true;
        mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
    } else if (button == GLUT_RIGHT_BUTTON) {
        bRightMouse = true;
        mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
    }
}

void GameState::mouseRelease(int button) {
    if (button == GLUT_LEFT_BUTTON) {
        bLeftMouse = false;
        mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
    } else if (button == GLUT_RIGHT_BUTTON) {
        bRightMouse = false;
        mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
    }

}


