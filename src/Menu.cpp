#include "ShaderManager.h"
#include "Game.h"
#include "StateManager.h"

#include "Menu.h"
#include "EventCreator.h"

Menu::Menu(Game *game) : GameState(game), _mode(LevelModes::Mode::FUN_MODE) {
    music = make_unique<Sound>(_game->getSoundManager(), "sounds/MenuSong.ogg",
                               FMOD_LOOP_NORMAL | FMOD_CREATESTREAM);

    initTextures();

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
    menuMode->changeAnimation(LevelModes::convertToInt(_mode));

    menuExit = Sprite::createSprite(glm::vec2(111, 52), glm::vec2(1.f, 1.f),
                                    &ShaderManager::getInstance().getShaderProgram(), &menuExitTexture);
    menuAbout = Sprite::createSprite(glm::vec2(111, 52), glm::vec2(1.f, 1.f),
                                     &ShaderManager::getInstance().getShaderProgram(), &menuAboutTexture);
}

Menu::~Menu() = default;

void Menu::init() {
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
    _currentTime += static_cast<float>(deltaTime);
    menuMode->changeAnimation(LevelModes::convertToInt(_mode));
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
    switch (_mode) {
        case LevelModes::Mode::FUN_MODE:
            _mode = LevelModes::Mode::TRICKY_MODE;
            break;
        case LevelModes::Mode::TRICKY_MODE:
            _mode = LevelModes::Mode::TAXING_MODE;
            break;
        default:
            return;
    }
}

void Menu::changeModeDown() {
    switch (_mode) {
        case LevelModes::Mode::TAXING_MODE:
            _mode = LevelModes::Mode::TRICKY_MODE;
            break;
        case LevelModes::Mode::TRICKY_MODE:
            _mode = LevelModes::Mode::FUN_MODE;
            break;
        default:
            return;
    }
}

LevelModes::Mode Menu::getMode() const {
    return _mode;
}

void Menu::endMusic() {
    music->stopSound();
}

void Menu::mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton) {

}

void Menu::onKeyPressed(const SDL_KeyboardEvent &keyboardEvent) {

    switch (keyboardEvent.keysym.sym) {
        case SDLK_F1:
            // key f1 go to playing
            endMusic();
            {
                int *mode = new int(LevelModes::convertToInt(getMode()));
                int *number = new int(1);
                EventCreator::sendSimpleUserEvent(CHANGE_TO_INFO, mode, number);
            }
            break;
        case SDLK_F2:
            // F2 go to Instructions
            endMusic();
            EventCreator::sendSimpleUserEvent(CHANGE_TO_INSTRUCTION);
            break;
        case SDLK_F3:
            // F3 go to About
            endMusic();
            EventCreator::sendSimpleUserEvent(CHANGE_TO_CREDITS);
            //_game->getStateManager()->changeCredits();
            break;
        case SDLK_UP:
            changeModeUp();
            break;
        case SDLK_DOWN:
            changeModeDown();
            break;
        case SDLK_ESCAPE:
            endMusic();

            SDL_Event quitEvent;
            SDL_memset(&quitEvent, 0, sizeof(quitEvent));
            quitEvent.type = SDL_QUIT;
            SDL_PushEvent(&quitEvent);
            break;
        case SDLK_h:
            _game->swapDifficultyMode();
            break;
    }
}


