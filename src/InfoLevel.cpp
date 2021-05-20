#include <GL/glew.h>

#include "ShaderManager.h"
#include "KeyFactory.h"
#include "StateManager.h"
#include "GameState.h"
#include "EventCreator.h"
#include "InfoLevel.h"


InfoLevel::InfoLevel(Game * game, LevelModes::Mode mode, int level) : GameState(game), _mode(mode), _level(level){
    initTextures();

    _leftKey = KeyFactory::createLeftKey(glm::vec2(25, 15));
    _menuWord = std::make_unique<Word>("MENU");

    _rightKey = KeyFactory::createRightKey(glm::vec2(25, 15));
    _playWord = std::make_unique<Word>("PLAY");
}

InfoLevel::~InfoLevel() = default;

void InfoLevel::init() {
    _currentTime = 0.0f;

    _leftKey->setPosition(glm::vec2(5, 173));
    _menuWord->setPosition(glm::vec2(36, 173));
    _rightKey->setPosition(glm::vec2(280, 173));
    _playWord->setPosition(glm::vec2(240, 173));
}

void InfoLevel::setLevel(LevelModes::Mode levelMode, int numLevel) {
    _level = numLevel;
    _mode = levelMode;

    initTextures();

    _infoLevelSprite = Sprite::createSprite(glm::vec2(CAMERA_WIDTH, CAMERA_HEIGHT), glm::vec2(1.f, 1.f),
                                            &ShaderManager::getInstance().getShaderProgram(), &_infoLevelTexture);
}

void InfoLevel::update(int deltaTime) {
    _currentTime += static_cast<float>(deltaTime);
}

void InfoLevel::render() {
    ShaderManager::getInstance().useShaderProgram();

    _infoLevelSprite->render();
    _menuWord->render();
    _rightKey->render();
    _playWord->render();
    _leftKey->render();
}

void InfoLevel::initTextures() {

    _infoLevelTexture.loadFromFile("images/levels/" + LevelModes::convertToString(_mode) + to_string(_level) + "/info.png", TEXTURE_PIXEL_FORMAT_RGBA);
    _infoLevelTexture.setMinFilter(GL_NEAREST);
    _infoLevelTexture.setMagFilter(GL_NEAREST);

}

LevelModes::Mode InfoLevel::getMode() const {
    return _mode;
}

int InfoLevel::getLevel() const {
    return _level;
}

void InfoLevel::onKeyPressed(const SDL_KeyboardEvent &keyboardEvent) {
    switch (keyboardEvent.keysym.sym) {
        case SDLK_ESCAPE:
            EventCreator::sendSimpleUserEvent(CHANGE_TO_MENU);
            break;
        case SDLK_RIGHT: {
            int *mode = new int(LevelModes::convertToInt(getMode()));
            int *number = new int(1);
            EventCreator::sendSimpleUserEvent(CHANGE_TO_SCENE, mode, number);
            break;
        }
        case SDLK_LEFT:
            EventCreator::sendSimpleUserEvent(CHANGE_TO_MENU);
            break;
    }
}

void InfoLevel::mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton) {

}




