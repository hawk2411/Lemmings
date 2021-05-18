#include <GL/glew.h>
#include "InfoLevel.h"
#include "ShaderManager.h"
#include "KeyFactory.h"
#include "StateManager.h"

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

    _InfoLevelSprite = Sprite::createSprite(glm::vec2(CAMERA_WIDTH, CAMERA_HEIGHT), glm::vec2(1.f, 1.f),
                                            &ShaderManager::getInstance().getShaderProgram(), &_InfoLevelTexture);
    initSprites();
}

void InfoLevel::update(int deltaTime) {
    _currentTime += static_cast<float>(deltaTime);
}

void InfoLevel::render() {
    ShaderManager::getInstance().useShaderProgram();

    _InfoLevelSprite->render();
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

    _InfoLevelTexture.loadFromFile("images/levels/" + levelName + "/info.png", TEXTURE_PIXEL_FORMAT_RGBA);
    _InfoLevelTexture.setMinFilter(GL_NEAREST);
    _InfoLevelTexture.setMagFilter(GL_NEAREST);

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
            StateManager::instance().changeMenu();
            break;
        case SDLK_RIGHT:
            StateManager::instance().changeScene(getMode(), getLevel());
            break;
        case SDLK_LEFT:
            StateManager::instance().changeMenu();
            break;
    }
}

void InfoLevel::mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton) {

}

InfoLevel::~InfoLevel() {

}



