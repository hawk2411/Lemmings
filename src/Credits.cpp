#include "UserEvent.h"
#include "Credits.h"
#include "ShaderManager.h"
#include "Game.h"
#include "StateManager.h"
#include "MusicFabric.hpp"

Credits::Credits(Game *game) : GameState(game), _shaderManager(_game->getShaderManager()),
                               _music(createMusic("sounds/CreditsSong.ogg")) {

    _creditsLevelTexture.loadFromFile("images/credits.png", PixelFormat::TEXTURE_PIXEL_FORMAT_RGBA);
    _creditsLevelTexture.setMinFilter(GL_NEAREST);
    _creditsLevelTexture.setMagFilter(GL_NEAREST);

    _creditsLevelSprite = Sprite::createSprite(glm::vec2(CAMERA_WIDTH, CAMERA_HEIGHT), glm::vec2(1.f, 1.f),
                                               &_shaderManager->getShaderProgram(), &_creditsLevelTexture);

}

Credits::~Credits() = default;


void Credits::init() {
    _currentTime = 0.0f;
    Mix_PlayMusic(_music.get(), -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME);
}

void Credits::update(int deltaTime) {
    _currentTime += static_cast<float>(deltaTime);
}

void Credits::render() {
    _shaderManager->useShaderProgram();
    _creditsLevelSprite->render();
}


void Credits::endMusic() {
    Mix_HaltMusic();
}

void Credits::mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton) {

}

void Credits::onKeyPressed(const SDL_KeyboardEvent &keyboardEvent) {
    if (keyboardEvent.keysym.sym == SDLK_ESCAPE) {
        UserEvent<CHANGE_TO_MENU>::sendEvent();
        endMusic();
    }
}
