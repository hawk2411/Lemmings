#include "GameState.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include "common_defs.h"

GameState::GameState() {

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

    float aspectRatioX = (float(CAMERA_WIDTH) / windowWidth);
    float aspectRatioy = (float(CAMERA_HEIGHT) / windowHeight);
    mouseX = x * aspectRatioX;
    mouseY = y * aspectRatioy;

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


