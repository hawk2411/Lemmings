#include "Credits.h"
#include "ShaderManager.h"
#include "Game.h"
#include "StateManager.h"

Credits::Credits(Game *game) : GameState(game) {
    music = make_unique<Sound>(game->getSoundManager(), "sounds/CreditsSong.ogg",
                               FMOD_LOOP_NORMAL | FMOD_CREATESTREAM);
}

Credits::~Credits() {

}


void Credits::init() {
    _currentTime = 0.0f;
    initTextures();
    creditsLevelSprite = Sprite::createSprite(glm::vec2(CAMERA_WIDTH, CAMERA_HEIGHT), glm::vec2(1.f, 1.f),
                                              &ShaderManager::getInstance().getShaderProgram(), &creditsLevelTexture);
    music->playSound();
    music->setVolume(1.f);
}

void Credits::update(int deltaTime) {
    _currentTime += static_cast<float>(deltaTime);
}

void Credits::render() {
    ShaderManager::getInstance().useShaderProgram();
    creditsLevelSprite->render();
}

void Credits::initTextures() {
    creditsLevelTexture.loadFromFile("images/credits.png", TEXTURE_PIXEL_FORMAT_RGBA);
    creditsLevelTexture.setMinFilter(GL_NEAREST);
    creditsLevelTexture.setMagFilter(GL_NEAREST);

}

void Credits::endMusic() {
    music->stopSound();
}

void Credits::mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton) {

}

void Credits::onKeyPressed(const SDL_KeyboardEvent &keyboardEvent) {
    if (keyboardEvent.keysym.sym == SDLK_ESCAPE) {
        _game->getStateManager()->changeMenu();
        endMusic();
    }
}
