#include <GL/glew.h>
#include "common_defs.h"
#include "Game.h"
#include "GameState.h"

GameState::GameState(Game *game) :
        _currentTime(0.0),
        mouseX(0),
        mouseY(0),
        _game(game){
}

GameState::~GameState() {

}

void GameState::onMouseMove(const SDL_MouseMotionEvent &motionEvent) {

    int windowWidth;
    int windowHeight;

    auto window =  SDL_GetGrabbedWindow();
    SDL_GL_GetDrawableSize(window, &windowWidth, &windowHeight);

    float aspectRatioX = (float(CAMERA_WIDTH) / static_cast<float>(windowWidth));
    float aspectRatioY = (float(CAMERA_HEIGHT) / static_cast<float>(windowHeight));
    mouseX = static_cast<int>(static_cast<float>(motionEvent.x) * aspectRatioX);
    mouseY = static_cast<int>(static_cast<float>(motionEvent.y) * aspectRatioY);
    mouseMoved(mouseX, mouseY, (motionEvent.state & SDL_BUTTON(SDL_BUTTON_LEFT)), motionEvent.state & SDL_BUTTON(SDL_BUTTON_RIGHT));
}

void GameState::onMouseButtonDown(const SDL_MouseButtonEvent &buttonEvent) {
    switch( buttonEvent.button) {
        case SDL_BUTTON_LEFT:
            mouseMoved(mouseX, mouseY, (buttonEvent.state & SDL_BUTTON(SDL_BUTTON_LEFT)),
                       buttonEvent.state & SDL_BUTTON(SDL_BUTTON_RIGHT));
            break;
        case SDL_BUTTON_RIGHT:
            mouseMoved(mouseX, mouseY, (buttonEvent.state & SDL_BUTTON(SDL_BUTTON_LEFT)),
                       buttonEvent.state & SDL_BUTTON(SDL_BUTTON_RIGHT));
            break;
    }

}

void GameState::onMouseButtonUp(const SDL_MouseButtonEvent &buttonEvent) {
    switch( buttonEvent.button) {
        case SDL_BUTTON_LEFT:
            mouseMoved(mouseX, mouseY, (buttonEvent.state & SDL_BUTTON(SDL_BUTTON_LEFT)),
                       buttonEvent.state & SDL_BUTTON(SDL_BUTTON_RIGHT));
            break;
        case SDL_BUTTON_RIGHT:
            mouseMoved(mouseX, mouseY, (buttonEvent.state & SDL_BUTTON(SDL_BUTTON_LEFT)),
                       buttonEvent.state & SDL_BUTTON(SDL_BUTTON_RIGHT));
            break;
    }

}
