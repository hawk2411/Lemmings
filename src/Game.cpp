#include <memory>

#include "Game.h"
#include "UserEvent.h"

Game::Game() : _continueGame(true), _difficultyMode(Difficulties::Mode::Easy) {

    glClearColor(0.f, 0.f, 0.f, 1.0f);  //TODO glClearColor here???

    _shaderManager = std::make_unique<ShaderManager>();
    _stateManager = std::make_unique<StateManager>(this, _shaderManager.get());

    initSpriteSheets();
    _hardModeIndicator = Sprite::createSprite(glm::ivec2(20, 20), glm::vec2(136. / 256, 160. / 256),
                                              &_shaderManager->getShaderProgram(),
                                              &Game::spriteSheets().skullSprite);
    _hardModeIndicator->setPosition(glm::vec2(CAMERA_WIDTH - 26, 5));

}


void Game::render() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _stateManager->render();
    if (_difficultyMode == Difficulties::Mode::Hard) {
        _hardModeIndicator->render();
    }

}

void Game::initSpriteSheets() {

    Game::spriteSheets().greenNumLetters.loadFromFile("images/UI/lemm_font.png", PixelFormat::TEXTURE_PIXEL_FORMAT_RGBA);
    Game::spriteSheets().greenNumLetters.setMinFilter(GL_NEAREST);
    Game::spriteSheets().greenNumLetters.setMagFilter(GL_NEAREST);

    Game::spriteSheets().cursorSprites.loadFromFile("images/UI/cursor.png", PixelFormat::TEXTURE_PIXEL_FORMAT_RGBA);
    Game::spriteSheets().cursorSprites.setMinFilter(GL_NEAREST);
    Game::spriteSheets().cursorSprites.setMagFilter(GL_NEAREST);

    Game::spriteSheets().lemmingAnimations.loadFromFile("images/lemming_anim.png", PixelFormat::TEXTURE_PIXEL_FORMAT_RGBA);
    Game::spriteSheets().lemmingAnimations.setMinFilter(GL_NEAREST);
    Game::spriteSheets().lemmingAnimations.setMagFilter(GL_NEAREST);

    Game::spriteSheets().rotatedLemmingAnimations.loadFromFile("images/rotated_lemming_anim.png",
                                                               PixelFormat::TEXTURE_PIXEL_FORMAT_RGBA);
    Game::spriteSheets().rotatedLemmingAnimations.setMinFilter(GL_NEAREST);
    Game::spriteSheets().rotatedLemmingAnimations.setMagFilter(GL_NEAREST);

    Game::spriteSheets().doorSprites.loadFromFile("images/levels/lemming_doors.png", PixelFormat::TEXTURE_PIXEL_FORMAT_RGBA);
    Game::spriteSheets().doorSprites.setMinFilter(GL_NEAREST);
    Game::spriteSheets().doorSprites.setMagFilter(GL_NEAREST);

    Game::spriteSheets().trapdoorSprites.loadFromFile("images/levels/lemming_trapdoors.png", PixelFormat::TEXTURE_PIXEL_FORMAT_RGBA);
    Game::spriteSheets().trapdoorSprites.setMinFilter(GL_NEAREST);
    Game::spriteSheets().trapdoorSprites.setMagFilter(GL_NEAREST);

    Game::spriteSheets().buttonSprites.loadFromFile("images/UI/buttons.png", PixelFormat::TEXTURE_PIXEL_FORMAT_RGBA);
    Game::spriteSheets().buttonSprites.setMinFilter(GL_NEAREST);
    Game::spriteSheets().buttonSprites.setMagFilter(GL_NEAREST);

    Game::spriteSheets().numSprites.loadFromFile("images/UI/nums.png", PixelFormat::TEXTURE_PIXEL_FORMAT_RGBA);
    Game::spriteSheets().numSprites.setMinFilter(GL_NEAREST);
    Game::spriteSheets().numSprites.setMagFilter(GL_NEAREST);

    Game::spriteSheets().greenNumSprites.loadFromFile("images/UI/green_nums.png", PixelFormat::TEXTURE_PIXEL_FORMAT_RGBA);
    Game::spriteSheets().greenNumSprites.setMinFilter(GL_NEAREST);
    Game::spriteSheets().greenNumSprites.setMagFilter(GL_NEAREST);

    Game::spriteSheets().purpleNumSprites.loadFromFile("images/results/pink_nums.png", PixelFormat::TEXTURE_PIXEL_FORMAT_RGBA);
    Game::spriteSheets().purpleNumSprites.setMinFilter(GL_NEAREST);
    Game::spriteSheets().purpleNumSprites.setMagFilter(GL_NEAREST);

    Game::spriteSheets().jobNamesSprites.loadFromFile("images/UI/work_names.png", PixelFormat::TEXTURE_PIXEL_FORMAT_RGBA);
    Game::spriteSheets().jobNamesSprites.setMinFilter(GL_NEAREST);
    Game::spriteSheets().jobNamesSprites.setMagFilter(GL_NEAREST);

    Game::spriteSheets().infoWordSprites.loadFromFile("images/UI/reserved_words.png", PixelFormat::TEXTURE_PIXEL_FORMAT_RGBA);
    Game::spriteSheets().infoWordSprites.setMinFilter(GL_NEAREST);
    Game::spriteSheets().infoWordSprites.setMagFilter(GL_NEAREST);

    Game::spriteSheets().resultsWordSprites.loadFromFile("images/results/buttons.png", PixelFormat::TEXTURE_PIXEL_FORMAT_RGBA);
    Game::spriteSheets().resultsWordSprites.setMinFilter(GL_NEAREST);
    Game::spriteSheets().resultsWordSprites.setMagFilter(GL_NEAREST);

    Game::spriteSheets().stepSprite.loadFromFile("images/builderStep.png", PixelFormat::TEXTURE_PIXEL_FORMAT_RGBA);
    Game::spriteSheets().stepSprite.setMinFilter(GL_NEAREST);
    Game::spriteSheets().stepSprite.setMagFilter(GL_NEAREST);

    Game::spriteSheets().keySprites.loadFromFile("images/keys.png", PixelFormat::TEXTURE_PIXEL_FORMAT_RGBA);
    Game::spriteSheets().keySprites.setMinFilter(GL_NEAREST);
    Game::spriteSheets().keySprites.setMagFilter(GL_NEAREST);

    Game::spriteSheets().particleSprites.loadFromFile("images/particles.png", PixelFormat::TEXTURE_PIXEL_FORMAT_RGBA);
    Game::spriteSheets().particleSprites.setMinFilter(GL_NEAREST);
    Game::spriteSheets().particleSprites.setMagFilter(GL_NEAREST);

    Game::spriteSheets().skullSprite.loadFromFile("images/UI/skull.png", PixelFormat::TEXTURE_PIXEL_FORMAT_RGBA);
    Game::spriteSheets().skullSprite.setMinFilter(GL_NEAREST);
    Game::spriteSheets().skullSprite.setMagFilter(GL_NEAREST);
}

void Game::changeBplay() {
    _continueGame = !_continueGame;
}

Difficulties::Mode Game::getDifficultyMode() const {
    return _difficultyMode;
}

void Game::swapDifficultyMode() {
    _difficultyMode = (_difficultyMode == Difficulties::Mode::Easy) ? Difficulties::Mode::Hard : Difficulties::Mode::Easy;
}

StateManager *Game::getStateManager() {
    return _stateManager.get();
}

void Game::onUserEvent(const SDL_UserEvent &event) {
    _stateManager->onUserEvent(event);
}
