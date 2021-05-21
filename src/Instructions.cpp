#include "Instructions.h"
#include "Utils.h"
#include "ShaderManager.h"
#include "KeyFactory.h"
#include "StateManager.h"
#include "Game.h"
#include "EventCreator.h"

Instructions::Instructions(Game *game) : actualPage(0),
                                         _onlyLeft(false),
                                         _onlyRight(true), GameState(game) {

    _music = make_unique<Sound>(game->getSoundManager(), "sounds/InstructionsSong.ogg",
                                FMOD_LOOP_NORMAL | FMOD_CREATESTREAM);
    _leftKey = KeyFactory::createLeftKey();
    _rightKey = KeyFactory::createRightKey();
    _instructionsLevelTexture.loadFromFile("images/menu/menuBackground.png", TEXTURE_PIXEL_FORMAT_RGBA);
    _instructionsLevelTexture.setMinFilter(GL_NEAREST);
    _instructionsLevelTexture.setMagFilter(GL_NEAREST);
    _instructionsWord = make_unique<Word>("INSTRUCTIONS");
    _escapeKey = KeyFactory::createEscapeKey();
    _instructionsLevelSprite = Sprite::createSprite(glm::vec2(CAMERA_WIDTH, CAMERA_HEIGHT), glm::vec2(1.f, 1.f),
                                                    &ShaderManager::getInstance().getShaderProgram(),
                                                    &_instructionsLevelTexture);
    _instructionPages.push_back(make_unique<Word>("Welcome to Lemmings!"));
    _instructionPages.push_back(make_unique<Word>("Your goal is to save as"));
    _instructionPages.push_back(make_unique<Word>("many Lemmings as possible."));
    _instructionPages.push_back(make_unique<Word>("In order to do that, assign"));
    _instructionPages.push_back(make_unique<Word>("JOBS to your Lemmings and get"));
    _instructionPages.push_back(make_unique<Word>("them to the level exit."));
    _instructionPages.push_back(make_unique<Word>("To assign jobs to Lemmings,"));
    _instructionPages.push_back(make_unique<Word>("just click in the"));
    _instructionPages.push_back(make_unique<Word>("corresponding button on"));
    _instructionPages.push_back(make_unique<Word>("the bottom of the screen"));
    _instructionPages.push_back(make_unique<Word>("and then click into a Lemming."));
    _instructionPages.push_back(make_unique<Word>("Next lets see all the jobs!"));
    _instructionPages.push_back(make_unique<Word>("WALKER"));
    _instructionPages.push_back(make_unique<Word>("The Walker is very simple:"));
    _instructionPages.push_back(make_unique<Word>("He walks."));
    _instructionPages.push_back(make_unique<Word>("FALLER"));
    _instructionPages.push_back(make_unique<Word>("His destiny is to follow the"));
    _instructionPages.push_back(make_unique<Word>("laws of the gravity. CAUTION!"));
    _instructionPages.push_back(make_unique<Word>("BLOCKER"));
    _instructionPages.push_back(make_unique<Word>("He will block every Lemming in"));
    _instructionPages.push_back(make_unique<Word>("sight with his strong hands."));
    _instructionPages.push_back(make_unique<Word>("CLIMBER"));
    _instructionPages.push_back(make_unique<Word>("His destiny is to defy the"));
    _instructionPages.push_back(make_unique<Word>("laws of the gravity. GG"));
    _instructionPages.push_back(make_unique<Word>("FLOATER"));
    _instructionPages.push_back(make_unique<Word>("Unlike FALLER, he will not"));
    _instructionPages.push_back(make_unique<Word>("die from falling."));
    _instructionPages.push_back(make_unique<Word>("BOMBER"));
    _instructionPages.push_back(make_unique<Word>("He likes explosions. A lot."));
    _instructionPages.push_back(make_unique<Word>("KABOOM!"));
    _instructionPages.push_back(make_unique<Word>("BUILDER"));
    _instructionPages.push_back(make_unique<Word>("He builds stairs to help"));
    _instructionPages.push_back(make_unique<Word>("other Lemmings to go on."));
    _instructionPages.push_back(make_unique<Word>("DIGGER"));
    _instructionPages.push_back(make_unique<Word>("He will eventually arrive"));
    _instructionPages.push_back(make_unique<Word>("to the center of the earth."));
    _instructionPages.push_back(make_unique<Word>("BASHER"));
    _instructionPages.push_back(make_unique<Word>("He will clear the way"));
    _instructionPages.push_back(make_unique<Word>("in a straight line."));
    _instructionPages.push_back(make_unique<Word>("MINER"));
    _instructionPages.push_back(make_unique<Word>("He is looking for gold"));
    _instructionPages.push_back(make_unique<Word>("in a diagonal direction."));
    _instructionPages.push_back(make_unique<Word>("Finally, if you feel confident"));
    _instructionPages.push_back(make_unique<Word>("enough you can activate hard"));
    _instructionPages.push_back(make_unique<Word>("mode by pressing H in the"));
    _instructionPages.push_back(make_unique<Word>("MENU. You will notice that"));
    _instructionPages.push_back(make_unique<Word>("HARD MODE is active seeing a"));
    _instructionPages.push_back(make_unique<Word>("skull in the top right corner."));
    _instructionPages.push_back(make_unique<Word>("In hard mode the map"));
    _instructionPages.push_back(make_unique<Word>("regenerates itself over time,"));
    _instructionPages.push_back(make_unique<Word>("so be carefull!"));
    _instructionPages.push_back(make_unique<Word>(""));
    _instructionPages.push_back(make_unique<Word>(""));
    _instructionPages.push_back(make_unique<Word>(""));

}

Instructions::~Instructions() = default;

void Instructions::init() {
    _currentTime = 0.0f;
    _onlyRight = true;
    _onlyLeft = false;
    actualPage = 0;
    _music->playSound();
    _music->setVolume(1.f);
    _rightKey->setPosition(glm::vec2(230, 160));
    _leftKey->setPosition(glm::vec2(200, 160));
    _escapeKey->setPosition(glm::vec2(30, 160));
    _instructionsWord->setPosition(glm::vec2(75, 170));
    _instructionPages[0]->setPosition(glm::vec2(10, 10));
    _instructionPages[1]->setPosition(glm::vec2(10, 30));
    _instructionPages[2]->setPosition(glm::vec2(10, 50));
    _instructionPages[3]->setPosition(glm::vec2(10, 80));
    _instructionPages[4]->setPosition(glm::vec2(10, 100));
    _instructionPages[5]->setPosition(glm::vec2(10, 120));
    _instructionPages[6]->setPosition(glm::vec2(10, 10));
    _instructionPages[7]->setPosition(glm::vec2(10, 30));
    _instructionPages[8]->setPosition(glm::vec2(10, 50));
    _instructionPages[9]->setPosition(glm::vec2(10, 70));
    _instructionPages[10]->setPosition(glm::vec2(10, 90));
    _instructionPages[11]->setPosition(glm::vec2(10, 130));
    _instructionPages[12]->setPosition(glm::vec2(10, 10));
    _instructionPages[13]->setPosition(glm::vec2(10, 30));
    _instructionPages[14]->setPosition(glm::vec2(10, 50));
    _instructionPages[15]->setPosition(glm::vec2(10, 90));
    _instructionPages[16]->setPosition(glm::vec2(10, 110));
    _instructionPages[17]->setPosition(glm::vec2(10, 130));
    _instructionPages[18]->setPosition(glm::vec2(10, 10));
    _instructionPages[19]->setPosition(glm::vec2(10, 30));
    _instructionPages[20]->setPosition(glm::vec2(10, 50));
    _instructionPages[21]->setPosition(glm::vec2(10, 90));
    _instructionPages[22]->setPosition(glm::vec2(10, 110));
    _instructionPages[23]->setPosition(glm::vec2(10, 130));
    _instructionPages[24]->setPosition(glm::vec2(10, 10));
    _instructionPages[25]->setPosition(glm::vec2(10, 30));
    _instructionPages[26]->setPosition(glm::vec2(10, 50));
    _instructionPages[27]->setPosition(glm::vec2(10, 90));
    _instructionPages[28]->setPosition(glm::vec2(10, 110));
    _instructionPages[29]->setPosition(glm::vec2(10, 130));
    _instructionPages[30]->setPosition(glm::vec2(10, 10));
    _instructionPages[31]->setPosition(glm::vec2(10, 30));
    _instructionPages[32]->setPosition(glm::vec2(10, 50));
    _instructionPages[33]->setPosition(glm::vec2(10, 90));
    _instructionPages[34]->setPosition(glm::vec2(10, 110));
    _instructionPages[35]->setPosition(glm::vec2(10, 130));
    _instructionPages[36]->setPosition(glm::vec2(10, 10));
    _instructionPages[37]->setPosition(glm::vec2(10, 30));
    _instructionPages[38]->setPosition(glm::vec2(10, 50));
    _instructionPages[39]->setPosition(glm::vec2(10, 90));
    _instructionPages[40]->setPosition(glm::vec2(10, 110));
    _instructionPages[41]->setPosition(glm::vec2(10, 130));
    _instructionPages[42]->setPosition(glm::vec2(10, 10));
    _instructionPages[43]->setPosition(glm::vec2(10, 30));
    _instructionPages[44]->setPosition(glm::vec2(10, 50));
    _instructionPages[45]->setPosition(glm::vec2(10, 70));
    _instructionPages[46]->setPosition(glm::vec2(10, 90));
    _instructionPages[47]->setPosition(glm::vec2(10, 110));
    _instructionPages[48]->setPosition(glm::vec2(10, 10));
    _instructionPages[49]->setPosition(glm::vec2(10, 30));
    _instructionPages[50]->setPosition(glm::vec2(10, 50));
    _instructionPages[51]->setPosition(glm::vec2(10, 90));
    _instructionPages[52]->setPosition(glm::vec2(10, 110));
    _instructionPages[53]->setPosition(glm::vec2(10, 130));
}

void Instructions::update(int deltaTime) {
    _currentTime +=  static_cast<float>(deltaTime);
}

void Instructions::render() {
    ShaderManager::getInstance().useShaderProgram();
    _instructionsLevelSprite->render();
    for (int i = actualPage; i < Utils::min(actualPage + LINES_PAGE, _instructionPages.size()); ++i) {
        _instructionPages[i]->render();
    }
    if (!_onlyRight) {
        _leftKey->render();
    }
    if (!_onlyLeft) {
        _rightKey->render();
    }

    _instructionsWord->render();

    _escapeKey->render();
}

void Instructions::passPageLeft() {
    if (actualPage - LINES_PAGE >= 0) {
        actualPage -= LINES_PAGE;
    }
    _onlyRight = actualPage < LINES_PAGE;
    _onlyLeft = actualPage + LINES_PAGE >= _instructionPages.size();
}


void Instructions::passPageRight() {
    if (actualPage + LINES_PAGE < _instructionPages.size()) {
        actualPage += LINES_PAGE;
    }

    _onlyRight = actualPage < LINES_PAGE;
    _onlyLeft = actualPage + LINES_PAGE >= _instructionPages.size();
}


void Instructions::endMusic() {
    _music->stopSound();
}

void Instructions::mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton) {

}

void Instructions::onKeyPressed(const SDL_KeyboardEvent &keyboardEvent) {
    switch (keyboardEvent.keysym.sym) {
        case SDLK_ESCAPE:
            endMusic();
            EventCreator::sendSimpleUserEvent(CHANGE_TO_MENU, nullptr, nullptr);
            break;
        case SDLK_RIGHT:
            passPageRight();
            break;
        case SDLK_LEFT:
            passPageLeft();
            break;;
    }
}

