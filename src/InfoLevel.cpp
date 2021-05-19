#include <GL/glew.h>

#include "ShaderManager.h"
#include "KeyFactory.h"
#include "StateManager.h"
#include "GameState.h"
#include "InfoLevel.h"


InfoLevel::InfoLevel(Game * game) : GameState(game){
    _currentTime = 0.0f;
}


void InfoLevel::init() {
    _currentTime = 0.0f;
}

void InfoLevel::setLevel(int numLevel, int levelMode) {
    _level = numLevel;
    _mode = levelMode;

    initTextures();

    _infoLevelSprite = Sprite::createSprite(glm::vec2(CAMERA_WIDTH, CAMERA_HEIGHT), glm::vec2(1.f, 1.f),
                                            &ShaderManager::getInstance().getShaderProgram(), &_infoLevelTexture);
    initSprites();
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

    string levelType;
    switch (_mode) {
        case FUN_MODE:
            levelType = "fun";
            break;
        case TRICKY_MODE:
            levelType = "tricky";
            break;
        case TAXING_MODE:
            levelType = "taxing";
            break;
    }

    string levelName = levelType + to_string(_level);

    _infoLevelTexture.loadFromFile("images/levels/" + levelName + "/info.png", TEXTURE_PIXEL_FORMAT_RGBA);
    _infoLevelTexture.setMinFilter(GL_NEAREST);
    _infoLevelTexture.setMagFilter(GL_NEAREST);

}

int InfoLevel::getMode() const {
    return _mode;
}

int InfoLevel::getLevel() const {
    return _level;
}

void InfoLevel::initSprites() {
    _leftKey = KeyFactory::instance().createLeftKey(glm::vec2(25, 15));
    _leftKey->setPosition(glm::vec2(5, 173));

    _menuWord = new Word("MENU");
    _menuWord->setPosition(glm::vec2(36, 173));

    _rightKey = KeyFactory::instance().createRightKey(glm::vec2(25, 15));
    _rightKey->setPosition(glm::vec2(280, 173));

    _playWord = new Word("PLAY");
    _playWord->setPosition(glm::vec2(240, 173));


}

void InfoLevel::onKeyPressed(const SDL_KeyboardEvent &keyboardEvent) {
    switch (keyboardEvent.keysym.sym) {
        case SDLK_ESCAPE:
            _game->getStateManager()->changeMenu();
            break;
        case SDLK_RIGHT:
            _game->getStateManager()->changeScene(getMode(), getLevel());
            break;
        case SDLK_LEFT:
            _game->getStateManager()->changeMenu();
            break;
    }
}

void InfoLevel::mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton) {

}

InfoLevel::~InfoLevel() {

}



