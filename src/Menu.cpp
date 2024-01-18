#include "ShaderManager.h"
#include "Game.h"

#include "UserEvent.h"
#include "Menu.h"
#include "LevelIndex.h"

Menu::Menu(Game *game, const LevelIndex &levelIndex) : GameState(game), _levelIndex(levelIndex), _shaderManager(_game->getShaderManager()), _music(
        createMusic("sounds/MenuSong.ogg")) {
    initTextures();

    _menuBackground = Sprite::createSprite(glm::vec2(320, 230), glm::vec2(1.f, 1.f),
                                           &_shaderManager->getShaderProgram(), &_menuTexture);
    _menuLogo = Sprite::createSprite(glm::vec2(250, 56), glm::vec2(1.f, 1.f),
                                     &_shaderManager->getShaderProgram(), &_menuLogoTexture);
    _menuPlaying = Sprite::createSprite(glm::vec2(111, 52), glm::vec2(1.f, 1.f),
                                        &_shaderManager->getShaderProgram(), &_menuPlayingTexture);
    _menuHelp = Sprite::createSprite(glm::vec2(111, 52), glm::vec2(1.f, 1.f),
                                     &_shaderManager->getShaderProgram(), &_menuHelpTexture);
    _menuMode = Sprite::createSprite(glm::vec2(111, 52), glm::vec2(1.f, 256. / 1024),
                                     &_shaderManager->getShaderProgram(), &_menuModeTexture);
    _menuMode->setNumberAnimations(3);
    for (int i = 0; i < 3; ++i) {
        _menuMode->addKeyframe(i, _modePositions[i]);
    }
    _menuMode->changeAnimation(LevelModes::convertToInt(_levelIndex.mode));

    _menuExit = Sprite::createSprite(glm::vec2(111, 52), glm::vec2(1.f, 1.f),
                                     &_shaderManager->getShaderProgram(), &_menuExitTexture);
    _menuAbout = Sprite::createSprite(glm::vec2(111, 52), glm::vec2(1.f, 1.f),
                                      &_shaderManager->getShaderProgram(), &_menuAboutTexture);
}

Menu::~Menu() = default;

void Menu::init() {
    _menuBackground->setPosition(glm::vec2(0, 0));
    _menuLogo->setPosition(glm::vec2(40, 10));
    _menuPlaying->setPosition(glm::vec2(35, 85));
    _menuHelp->setPosition(glm::vec2(126, 85));
    _menuMode->setPosition(glm::vec2(216, 85));
    _menuAbout->setPosition(glm::vec2(80, 130));
    _menuExit->setPosition(glm::vec2(171, 130));

    Mix_PlayMusic(_music.get(), 0);
    Mix_VolumeMusic(MIX_MAX_VOLUME);
}


void Menu::update(int deltaTime) {
    _currentTime += static_cast<float>(deltaTime);
    _menuMode->changeAnimation(LevelModes::convertToInt(_levelIndex.mode));
}

void Menu::render() {
    _shaderManager->useShaderProgram();
    _menuBackground->render();
    _menuLogo->render();
    _menuAbout->render();
    _menuHelp->render();

    _menuMode->render();

    _menuExit->render();
    _menuPlaying->render();
}

void Menu::initTextures() {

    _menuTexture.loadFromFile("images/menu/menuBackground.png", PixelFormat::TEXTURE_PIXEL_FORMAT_RGBA);
    _menuTexture.setMinFilter(GL_NEAREST);
    _menuTexture.setMagFilter(GL_NEAREST);

    _menuLogoTexture.loadFromFile("images/menu/logo.png", PixelFormat::TEXTURE_PIXEL_FORMAT_RGBA);
    _menuLogoTexture.setMinFilter(GL_NEAREST);
    _menuLogoTexture.setMagFilter(GL_NEAREST);

    _menuAboutTexture.loadFromFile("images/menu/aboutSprite.png", PixelFormat::TEXTURE_PIXEL_FORMAT_RGBA);
    _menuAboutTexture.setMinFilter(GL_NEAREST);
    _menuAboutTexture.setMagFilter(GL_NEAREST);

    _menuHelpTexture.loadFromFile("images/menu/helpSprite.png", PixelFormat::TEXTURE_PIXEL_FORMAT_RGBA);
    _menuHelpTexture.setMinFilter(GL_NEAREST);
    _menuHelpTexture.setMagFilter(GL_NEAREST);

    _menuExitTexture.loadFromFile("images/menu/exitSprite.png", PixelFormat::TEXTURE_PIXEL_FORMAT_RGBA);
    _menuExitTexture.setMinFilter(GL_NEAREST);
    _menuExitTexture.setMagFilter(GL_NEAREST);

    _menuModeTexture.loadFromFile("images/menu/modeSpriteSheet.png", PixelFormat::TEXTURE_PIXEL_FORMAT_RGBA);
    _menuModeTexture.setMinFilter(GL_NEAREST);
    _menuModeTexture.setMagFilter(GL_NEAREST);

    _menuPlayingTexture.loadFromFile("images/menu/player1Sprite.png", PixelFormat::TEXTURE_PIXEL_FORMAT_RGBA);
    _menuPlayingTexture.setMinFilter(GL_NEAREST);
    _menuPlayingTexture.setMagFilter(GL_NEAREST);
}

void Menu::changeModeUp() {
    switch (_levelIndex.mode) {
        case LevelModes::Mode::FUN_MODE:
            _levelIndex.mode = LevelModes::Mode::TRICKY_MODE;
            break;
        case LevelModes::Mode::TRICKY_MODE:
            _levelIndex.mode = LevelModes::Mode::TAXING_MODE;
            break;
        default:
            return;
    }
}

void Menu::changeModeDown() {
    switch (_levelIndex.mode) {
        case LevelModes::Mode::TAXING_MODE:
            _levelIndex.mode = LevelModes::Mode::TRICKY_MODE;
            break;
        case LevelModes::Mode::TRICKY_MODE:
            _levelIndex.mode = LevelModes::Mode::FUN_MODE;
            break;
        default:
            return;
    }
}

LevelModes::Mode Menu::getMode() const {
    return _levelIndex.mode;
}

void Menu::endMusic() {
    Mix_HaltMusic();
}

void Menu::mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton) {

}

void Menu::onKeyPressed(const SDL_KeyboardEvent &keyboardEvent) {

    switch (keyboardEvent.keysym.sym) {
        case SDLK_F1:
            // key f1 go to playing
            endMusic();
            UserEvent<CHANGE_TO_INFO, LevelIndex>::sendEvent(
                    new LevelIndex{_levelIndex.mode, _levelIndex.levelNo});
            break;
        case SDLK_F2:
            // F2 go to Instructions
            endMusic();
            UserEvent<CHANGE_TO_INSTRUCTION>::sendEvent();
            break;
        case SDLK_F3:
            // F3 go to About
            endMusic();
            UserEvent<CHANGE_TO_CREDITS>::sendEvent();
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


