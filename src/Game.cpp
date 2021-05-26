#include <memory>
#include "EventCreator.h"

#include "Game.h"


Game::Game() : bPlay(true), _dmode(Difficulties::Mode::Easy),
                prevTime(prevTime) {

    glClearColor(0.f, 0.f, 0.f, 1.0f);  //TODO glClearColor here???
    _soundManager = std::make_unique<SoundManager>();

    _shaderManager = std::make_unique<ShaderManager>();
    _stateManager = std::make_unique<StateManager>(this, _shaderManager.get());

    initSpriteSheets();
    hardModeIndicator = Sprite::createSprite(glm::ivec2(20, 20), glm::vec2(136. / 256, 160. / 256),
                                             &_shaderManager->getShaderProgram(),
                                             &Game::spriteSheets().skullSprite);
    hardModeIndicator->setPosition(glm::vec2(CAMERA_WIDTH - 26, 5));

}

void Game::init() {


}

bool Game::update(int deltaTime) {
    _stateManager->update(deltaTime);
    return bPlay;
}

void Game::render() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _stateManager->render();
    if (_dmode == Difficulties::Mode::Hard) {
        hardModeIndicator->render();
    }

}

void Game::initSpriteSheets() {

    Game::spriteSheets().greenNumLetters.loadFromFile("images/UI/lemm_font.png", TEXTURE_PIXEL_FORMAT_RGBA);
    Game::spriteSheets().greenNumLetters.setMinFilter(GL_NEAREST);
    Game::spriteSheets().greenNumLetters.setMagFilter(GL_NEAREST);

    Game::spriteSheets().cursorSprites.loadFromFile("images/UI/cursor.png", TEXTURE_PIXEL_FORMAT_RGBA);
    Game::spriteSheets().cursorSprites.setMinFilter(GL_NEAREST);
    Game::spriteSheets().cursorSprites.setMagFilter(GL_NEAREST);

    Game::spriteSheets().lemmingAnimations.loadFromFile("images/lemming_anim.png", TEXTURE_PIXEL_FORMAT_RGBA);
    Game::spriteSheets().lemmingAnimations.setMinFilter(GL_NEAREST);
    Game::spriteSheets().lemmingAnimations.setMagFilter(GL_NEAREST);

    Game::spriteSheets().rotatedLemmingAnimations.loadFromFile("images/rotated_lemming_anim.png",
                                                               TEXTURE_PIXEL_FORMAT_RGBA);
    Game::spriteSheets().rotatedLemmingAnimations.setMinFilter(GL_NEAREST);
    Game::spriteSheets().rotatedLemmingAnimations.setMagFilter(GL_NEAREST);

    Game::spriteSheets().doorSprites.loadFromFile("images/levels/lemming_doors.png", TEXTURE_PIXEL_FORMAT_RGBA);
    Game::spriteSheets().doorSprites.setMinFilter(GL_NEAREST);
    Game::spriteSheets().doorSprites.setMagFilter(GL_NEAREST);

    Game::spriteSheets().trapdoorSprites.loadFromFile("images/levels/lemming_trapdoors.png", TEXTURE_PIXEL_FORMAT_RGBA);
    Game::spriteSheets().trapdoorSprites.setMinFilter(GL_NEAREST);
    Game::spriteSheets().trapdoorSprites.setMagFilter(GL_NEAREST);

    Game::spriteSheets().buttonSprites.loadFromFile("images/UI/buttons.png", TEXTURE_PIXEL_FORMAT_RGBA);
    Game::spriteSheets().buttonSprites.setMinFilter(GL_NEAREST);
    Game::spriteSheets().buttonSprites.setMagFilter(GL_NEAREST);

    Game::spriteSheets().numSprites.loadFromFile("images/UI/nums.png", TEXTURE_PIXEL_FORMAT_RGBA);
    Game::spriteSheets().numSprites.setMinFilter(GL_NEAREST);
    Game::spriteSheets().numSprites.setMagFilter(GL_NEAREST);

    Game::spriteSheets().greenNumSprites.loadFromFile("images/UI/green_nums.png", TEXTURE_PIXEL_FORMAT_RGBA);
    Game::spriteSheets().greenNumSprites.setMinFilter(GL_NEAREST);
    Game::spriteSheets().greenNumSprites.setMagFilter(GL_NEAREST);

    Game::spriteSheets().purpleNumSprites.loadFromFile("images/results/pink_nums.png", TEXTURE_PIXEL_FORMAT_RGBA);
    Game::spriteSheets().purpleNumSprites.setMinFilter(GL_NEAREST);
    Game::spriteSheets().purpleNumSprites.setMagFilter(GL_NEAREST);

    Game::spriteSheets().jobNamesSprites.loadFromFile("images/UI/work_names.png", TEXTURE_PIXEL_FORMAT_RGBA);
    Game::spriteSheets().jobNamesSprites.setMinFilter(GL_NEAREST);
    Game::spriteSheets().jobNamesSprites.setMagFilter(GL_NEAREST);

    Game::spriteSheets().infoWordSprites.loadFromFile("images/UI/reserved_words.png", TEXTURE_PIXEL_FORMAT_RGBA);
    Game::spriteSheets().infoWordSprites.setMinFilter(GL_NEAREST);
    Game::spriteSheets().infoWordSprites.setMagFilter(GL_NEAREST);

    Game::spriteSheets().resultsWordSprites.loadFromFile("images/results/buttons.png", TEXTURE_PIXEL_FORMAT_RGBA);
    Game::spriteSheets().resultsWordSprites.setMinFilter(GL_NEAREST);
    Game::spriteSheets().resultsWordSprites.setMagFilter(GL_NEAREST);

    Game::spriteSheets().stepSprite.loadFromFile("images/builderStep.png", TEXTURE_PIXEL_FORMAT_RGBA);
    Game::spriteSheets().stepSprite.setMinFilter(GL_NEAREST);
    Game::spriteSheets().stepSprite.setMagFilter(GL_NEAREST);

    Game::spriteSheets().keySprites.loadFromFile("images/keys.png", TEXTURE_PIXEL_FORMAT_RGBA);
    Game::spriteSheets().keySprites.setMinFilter(GL_NEAREST);
    Game::spriteSheets().keySprites.setMagFilter(GL_NEAREST);

    Game::spriteSheets().particleSprites.loadFromFile("images/particles.png", TEXTURE_PIXEL_FORMAT_RGBA);
    Game::spriteSheets().particleSprites.setMinFilter(GL_NEAREST);
    Game::spriteSheets().particleSprites.setMagFilter(GL_NEAREST);

    Game::spriteSheets().skullSprite.loadFromFile("images/UI/skull.png", TEXTURE_PIXEL_FORMAT_RGBA);
    Game::spriteSheets().skullSprite.setMinFilter(GL_NEAREST);
    Game::spriteSheets().skullSprite.setMagFilter(GL_NEAREST);
}

void Game::changeBplay() {
    bPlay = !bPlay;
}

Difficulties::Mode Game::getDifficultyMode() const {
    return _dmode;
}

void Game::swapDifficultyMode() {
    _dmode = (_dmode == Difficulties::Mode::Easy)?Difficulties::Mode::Hard: Difficulties::Mode::Easy;
}

SoundManager *Game::getSoundManager() const {
    return _soundManager.get();
}


StateManager *Game::getStateManager() {
    return _stateManager.get();
}

void Game::onUserEvent(const SDL_UserEvent &event) {
    switch (event.code) {
        case UPDATE_EVENT: {
            int delay = *(int *) event.data1;
            update(delay);
        }
            break;
        default:
            _stateManager->onUserEvent(event);
    }

}


//Game *Game::instance() {
//    static Game G;
//    return &G;
//}

//void Game::drawCallback() {
//    Game::instance()->render();
//}

//void Game::idleCallback() {
//    int currentTime = glutGet(GLUT_ELAPSED_TIME);
//    int deltaTime = currentTime - Game::instance()->prevTime;
//
//    if (static_cast<float>(deltaTime) > TIME_PER_FRAME) {
//        // Every time we enter here is equivalent to a game loop execution
//        if (!Game::instance()->update(deltaTime))
//            exit(0);
//        Game::instance()->prevTime = currentTime;
//        glutPostRedisplay();
//    }
//}

//void Game::keyboardDownCallback(unsigned char key, int x, int y) {
//
////    Game::instance()->getGameState()->keyPressed(key);
//}
//
//void Game::keyboardUpCallback(unsigned char key, int x, int y) {
////    Game::instance()->getGameState()->keyReleased(key);
//}
//
//void Game::specialDownCallback(int key, int x, int y) {
////    Game::instance()->getGameState()->specialKeyPressed(key);
//}
//
//void Game::specialUpCallback(int key, int x, int y) {
////    Game::instance()->getGameState()->specialKeyReleased(key);
//}
//
//void Game::motionCallback(int x, int y) {
////    Game::instance()->getGameState()->mouseMove(x, y);
//}
