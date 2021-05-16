#include "Menu.h"
#include "ShaderManager.h"
#include "Game.h"
#include "StateManager.h"

Menu::Menu() : mode(0) {
    music = make_unique<Sound>(Game::instance()->getSoundManager(), "sounds/MenuSong.ogg", FMOD_LOOP_NORMAL | FMOD_CREATESTREAM);
}

Menu::~Menu() {

}

void Menu::init() {
    initTextures();

    mode = 0;
    currentTime = 0.0f;

    menuBackground = Sprite::createSprite(glm::vec2(320, 230), glm::vec2(1.f, 1.f),
                                          &ShaderManager::getInstance().getShaderProgram(), &menuTexture);
    menuLogo = Sprite::createSprite(glm::vec2(250, 56), glm::vec2(1.f, 1.f),
                                    &ShaderManager::getInstance().getShaderProgram(), &menuLogoTexture);
    menuPlaying = Sprite::createSprite(glm::vec2(111, 52), glm::vec2(1.f, 1.f),
                                       &ShaderManager::getInstance().getShaderProgram(), &menuPlayingTexture);
    menuHelp = Sprite::createSprite(glm::vec2(111, 52), glm::vec2(1.f, 1.f),
                                    &ShaderManager::getInstance().getShaderProgram(), &menuHelpTexture);
    menuMode = Sprite::createSprite(glm::vec2(111, 52), glm::vec2(1.f, 256. / 1024),
                                    &ShaderManager::getInstance().getShaderProgram(), &menuModeTexture);
    menuMode->setNumberAnimations(3);
    for (int i = 0; i < 3; ++i) {
        menuMode->addKeyframe(i, modePositions[i]);
    }
    menuMode->changeAnimation(mode);

    menuExit = Sprite::createSprite(glm::vec2(111, 52), glm::vec2(1.f, 1.f),
                                    &ShaderManager::getInstance().getShaderProgram(), &menuExitTexture);
    menuAbout = Sprite::createSprite(glm::vec2(111, 52), glm::vec2(1.f, 1.f),
                                     &ShaderManager::getInstance().getShaderProgram(), &menuAboutTexture);
    menuBackground->setPosition(glm::vec2(0, 0));
    menuLogo->setPosition(glm::vec2(40, 10));
    menuPlaying->setPosition(glm::vec2(35, 85));
    menuHelp->setPosition(glm::vec2(126, 85));
    menuMode->setPosition(glm::vec2(216, 85));
    menuAbout->setPosition(glm::vec2(80, 130));
    menuExit->setPosition(glm::vec2(171, 130));

    music->playSound();
    music->setVolume(1.0f);

}


void Menu::update(int deltaTime) {
    currentTime += deltaTime;
    changeMode();
}

void Menu::render() {
    ShaderManager::getInstance().useShaderProgram();
    menuBackground->render();
    menuLogo->render();
    menuAbout->render();
    menuHelp->render();

    menuMode->render();

    menuExit->render();
    menuPlaying->render();
}

void Menu::initTextures() {

    menuTexture.loadFromFile("images/menu/menuBackground.png", TEXTURE_PIXEL_FORMAT_RGBA);
    menuTexture.setMinFilter(GL_NEAREST);
    menuTexture.setMagFilter(GL_NEAREST);

    menuLogoTexture.loadFromFile("images/menu/logo.png", TEXTURE_PIXEL_FORMAT_RGBA);
    menuLogoTexture.setMinFilter(GL_NEAREST);
    menuLogoTexture.setMagFilter(GL_NEAREST);

    menuAboutTexture.loadFromFile("images/menu/aboutSprite.png", TEXTURE_PIXEL_FORMAT_RGBA);
    menuAboutTexture.setMinFilter(GL_NEAREST);
    menuAboutTexture.setMagFilter(GL_NEAREST);

    menuHelpTexture.loadFromFile("images/menu/helpSprite.png", TEXTURE_PIXEL_FORMAT_RGBA);
    menuHelpTexture.setMinFilter(GL_NEAREST);
    menuHelpTexture.setMagFilter(GL_NEAREST);

    menuExitTexture.loadFromFile("images/menu/exitSprite.png", TEXTURE_PIXEL_FORMAT_RGBA);
    menuExitTexture.setMinFilter(GL_NEAREST);
    menuExitTexture.setMagFilter(GL_NEAREST);

    menuModeTexture.loadFromFile("images/menu/modeSpriteSheet.png", TEXTURE_PIXEL_FORMAT_RGBA);
    menuModeTexture.setMinFilter(GL_NEAREST);
    menuModeTexture.setMagFilter(GL_NEAREST);

    menuPlayingTexture.loadFromFile("images/menu/player1Sprite.png", TEXTURE_PIXEL_FORMAT_RGBA);
    menuPlayingTexture.setMinFilter(GL_NEAREST);
    menuPlayingTexture.setMagFilter(GL_NEAREST);
}

void Menu::changeModeUp() {
    if (mode + 1 < 3) {
        ++mode;
    }
}

void Menu::changeModeDown() {
    if (mode - 1 >= 0) {
        --mode;
    }
}

void Menu::changeMode() {
    menuMode->changeAnimation(mode);
}

int Menu::getMode() const {
    return mode;
}

void Menu::endMusic() {
    music->stopSound();
}

void Menu::keyPressed(int key) {
    if (key == 27) // Escape code
    {
        Game::instance()->changeBplay();
        endMusic();
    } else if (key == 'h') // Hard mode
    {
        Game::instance()->swapDifficultyMode();
    }
}

void Menu::specialKeyPressed(int key) {
    if (key == GLUT_KEY_F1) { // key f1 go to playing
        int mode = getMode();
        endMusic();
        StateManager::instance().changeInfo(mode, 1);
    } else if (key == GLUT_KEY_F2) { // F2 go to Instructions
        endMusic();
        StateManager::instance().changeInstructions();
    } else if (key == GLUT_KEY_F3) { // F3 go to About
        endMusic();
        StateManager::instance().changeCredits();
    } else if (key == GLUT_KEY_UP) {
        changeModeUp();
    } else if (key == GLUT_KEY_DOWN) {
        changeModeDown();
    }
}

void Menu::mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton) {

}


