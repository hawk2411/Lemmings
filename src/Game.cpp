#include "Game.h"
#include "Menu.h"

void Game::init() {
    bPlay = true;
    hardMode = false;
    glClearColor(0.f, 0.f, 0.f, 1.0f);
    initSpriteSheets();
    ShaderManager::getInstance().init();
    hardModeIndicator = Sprite::createSprite(glm::ivec2(20, 20), glm::vec2(136. / 256, 160. / 256),
                                             &ShaderManager::getInstance().getShaderProgram(),
                                             &Game::spriteSheets().skullSprite);
    hardModeIndicator->setPosition(glm::vec2(CAMERA_WIDTH - 26, 5));

    gameState = &Menu::getInstance();
    gameState->init();
}

bool Game::update(int deltaTime) {
    gameState->update(deltaTime);

    return bPlay;
}

void Game::render() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gameState->render();
    if (hardMode) {
        hardModeIndicator->render();
    }

}

GameState *Game::getGameState() {
    return gameState;
}

void Game::setGameState(GameState *state) {
    gameState = state;
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

bool Game::isHardMode() const {
    return hardMode;
}

void Game::swapDifficultyMode() {
    hardMode = !hardMode;
}

const SoundManager *Game::getSoundManager() const {
    return &soundManager;
}

// Same for mouse button presses or releases
void Game::mouseCallback(int button, int state, int x, int y) {
    switch(state) {
        case GLUT_DOWN:
            Game::instance()->getGameState()->mousePress(button);
            break;
        case GLUT_UP:
            Game::instance()->getGameState()->mouseRelease(button);
            break;
        default:
            break;
    }
}

Game *Game::instance() {
    static Game G(glutGet(GLUT_ELAPSED_TIME));
    return &G;
}

void Game::drawCallback() {
    Game::instance()->render();
    glutSwapBuffers();
}

void Game::idleCallback() {
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    int deltaTime = currentTime - Game::instance()->prevTime;

    if (static_cast<float>(deltaTime) > TIME_PER_FRAME) {
        // Every time we enter here is equivalent to a game loop execution
        if (!Game::instance()->update(deltaTime))
            exit(0);
        Game::instance()->prevTime = currentTime;
        glutPostRedisplay();
    }
}

void Game::keyboardDownCallback(unsigned char key, int x, int y) {

    Game::instance()->getGameState()->keyPressed(key);
}

void Game::keyboardUpCallback(unsigned char key, int x, int y) {
    Game::instance()->getGameState()->keyReleased(key);
}

void Game::specialDownCallback(int key, int x, int y) {
    Game::instance()->getGameState()->specialKeyPressed(key);
}

void Game::specialUpCallback(int key, int x, int y) {
    Game::instance()->getGameState()->specialKeyReleased(key);
}

void Game::motionCallback(int x, int y) {
    Game::instance()->getGameState()->mouseMove(x, y);
}
