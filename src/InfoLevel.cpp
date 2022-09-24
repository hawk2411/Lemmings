#include <GL/glew.h>

#include "ShaderManager.h"
#include "KeyFactory.h"
#include "StateManager.h"
#include "GameState.h"
#include "InfoLevel.h"
#include "LevelIndex.h"
#include "UserEvent.h"

InfoLevel::InfoLevel(Game * game, const LevelIndex& index) : GameState(game), _levelIndex(index), _shaderManager(_game->getShaderManager()){
    initTextures();

    _leftKey = KeyFactory::createLeftKey(&_shaderManager->getShaderProgram(), glm::vec2(25, 15));
    _menuWord = std::make_unique<Word>("MENU", _shaderManager);

    _rightKey = KeyFactory::createRightKey(&_shaderManager->getShaderProgram(), glm::vec2(25, 15));
    _playWord = std::make_unique<Word>("PLAY", _shaderManager);

    _infoLevelSprite = Sprite::createSprite(glm::vec2(CAMERA_WIDTH, CAMERA_HEIGHT), glm::vec2(1.f, 1.f),
                                            &_shaderManager->getShaderProgram(), &_infoLevelTexture);
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
    _levelIndex.mode = levelMode;
    _levelIndex.levelNo = numLevel;

    initTextures();


}

void InfoLevel::update(int deltaTime) {
    _currentTime += static_cast<float>(deltaTime);
}

void InfoLevel::render() {
    _shaderManager->useShaderProgram();

    _infoLevelSprite->render();
    _menuWord->render();
    _rightKey->render();
    _playWord->render();
    _leftKey->render();
}

void InfoLevel::initTextures() {

    _infoLevelTexture.loadFromFile("images/levels/" + LevelModes::convertToString(_levelIndex.mode) + to_string(_levelIndex.levelNo) + "/info.png", PixelFormat::TEXTURE_PIXEL_FORMAT_RGBA);
    _infoLevelTexture.setMinFilter(GL_NEAREST);
    _infoLevelTexture.setMagFilter(GL_NEAREST);

}



void InfoLevel::onKeyPressed(const SDL_KeyboardEvent &keyboardEvent) {
    switch (keyboardEvent.keysym.sym) {
        case SDLK_ESCAPE:
            UserEvent<CHANGE_TO_MENU>::sendEvent();
            break;
        case SDLK_RIGHT: {
            UserEvent<CHANGE_TO_SCENE, LevelIndex>::sendEvent(new LevelIndex(_levelIndex));
            break;
        }
        case SDLK_LEFT:
            UserEvent<CHANGE_TO_MENU>::sendEvent();
            break;
    }
}

void InfoLevel::mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton) {

}




