#include "Instructions.h"
#include "Utils.h"
#include "ShaderManager.h"
#include "InstructionsMouseManager.h"
#include "InstructionsKeyboardManager.h"
#include "KeyFactory.h"
#include "Game.h"

//#define LINESPAGE 6

void Instructions::init() {
    currentTime = 0.0f;
    _onlyRight = true;
    _onlyLeft = false;
    actualPage = 0;
    initTextures();
    initSprites();
    mouseManager = &InstructionsMouseManager::getInstance();
    keyboardManager = &InstructionsKeyboardManager::getInstance();

    _music = Game::instance().getSoundManager()->loadSound("sounds/InstructionsSong.ogg",
                                                           FMOD_LOOP_NORMAL | FMOD_CREATESTREAM);
    _channel = Game::instance().getSoundManager()->playSound(_music);
    _channel->setVolume(1.f);
}

void Instructions::update(int deltaTime) {
    currentTime += deltaTime;

}

void Instructions::render() {
    ShaderManager::getInstance().useShaderProgram();
    _instructionsLevelSprite->render();
    for (int i = actualPage; i < Utils::min(actualPage + LINESPAGE, _instructionPages.size()); ++i) {
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

void Instructions::initTextures() {
    _instructionsLevelTexture.loadFromFile("images/menu/menuBackground.png", TEXTURE_PIXEL_FORMAT_RGBA);
    _instructionsLevelTexture.setMinFilter(GL_NEAREST);
    _instructionsLevelTexture.setMagFilter(GL_NEAREST);

}

void Instructions::initSprites() {

    _leftKey = KeyFactory::instance().createLeftKey();
    _leftKey->setPosition(glm::vec2(200, 160));

    _instructionsWord = new Word("INSTRUCTIONS");
    _instructionsWord->setPosition(glm::vec2(75, 170));

    _rightKey = KeyFactory::instance().createRightKey();
    _rightKey->setPosition(glm::vec2(230, 160));

    _escapeKey = KeyFactory::instance().createEscapeKey();
    _escapeKey->setPosition(glm::vec2(30, 160));

    _instructionsLevelSprite = Sprite::createSprite(glm::vec2(CAMERA_WIDTH, CAMERA_HEIGHT), glm::vec2(1.f, 1.f),
                                                    &ShaderManager::getInstance().getShaderProgram(),
                                                    &_instructionsLevelTexture);

    initLines();
}


void Instructions::passPageLeft() {
    if (actualPage - LINESPAGE >= 0) {
        actualPage -= LINESPAGE;
    }
    _onlyRight = actualPage < LINESPAGE;
    _onlyLeft = actualPage + LINESPAGE >= _instructionPages.size();
}

void Instructions::passPageRight() {
    if (actualPage + LINESPAGE < _instructionPages.size()) {
        actualPage += LINESPAGE;
    }

    _onlyRight = actualPage < LINESPAGE;
    _onlyLeft = actualPage + LINESPAGE >= _instructionPages.size();
}

void Instructions::initLines() {
    _instructionPages.clear();
    _instructionPages.resize(0);

    _instructionPages.push_back(new Word("Welcome to Lemmings!"));
    _instructionPages[0]->setPosition(glm::vec2(10, 10));

    _instructionPages.push_back(new Word("Your goal is to save as"));
    _instructionPages[1]->setPosition(glm::vec2(10, 30));

    _instructionPages.push_back(new Word("many Lemmings as possible."));
    _instructionPages[2]->setPosition(glm::vec2(10, 50));

    _instructionPages.push_back(new Word("In order to do that, assign"));
    _instructionPages[3]->setPosition(glm::vec2(10, 80));

    _instructionPages.push_back(new Word("JOBS to your Lemmings and get"));
    _instructionPages[4]->setPosition(glm::vec2(10, 100));

    _instructionPages.push_back(new Word("them to the level exit."));
    _instructionPages[5]->setPosition(glm::vec2(10, 120));


    _instructionPages.push_back(new Word("To assign jobs to Lemmings,"));
    _instructionPages[6]->setPosition(glm::vec2(10, 10));

    _instructionPages.push_back(new Word("just click in the"));
    _instructionPages[7]->setPosition(glm::vec2(10, 30));

    _instructionPages.push_back(new Word("corresponding button on"));
    _instructionPages[8]->setPosition(glm::vec2(10, 50));

    _instructionPages.push_back(new Word("the bottom of the screen"));
    _instructionPages[9]->setPosition(glm::vec2(10, 70));

    _instructionPages.push_back(new Word("and then click into a Lemming."));
    _instructionPages[10]->setPosition(glm::vec2(10, 90));

    _instructionPages.push_back(new Word("Next lets see all the jobs!"));
    _instructionPages[11]->setPosition(glm::vec2(10, 130));


    _instructionPages.push_back(new Word("WALKER"));
    _instructionPages[12]->setPosition(glm::vec2(10, 10));

    _instructionPages.push_back(new Word("The Walker is very simple:"));
    _instructionPages[13]->setPosition(glm::vec2(10, 30));

    _instructionPages.push_back(new Word("He walks."));
    _instructionPages[14]->setPosition(glm::vec2(10, 50));

    _instructionPages.push_back(new Word("FALLER"));
    _instructionPages[15]->setPosition(glm::vec2(10, 90));

    _instructionPages.push_back(new Word("His destiny is to follow the"));
    _instructionPages[16]->setPosition(glm::vec2(10, 110));

    _instructionPages.push_back(new Word("laws of the gravity. CAUTION!"));
    _instructionPages[17]->setPosition(glm::vec2(10, 130));


    _instructionPages.push_back(new Word("BLOCKER"));
    _instructionPages[18]->setPosition(glm::vec2(10, 10));

    _instructionPages.push_back(new Word("He will block every Lemming in"));
    _instructionPages[19]->setPosition(glm::vec2(10, 30));

    _instructionPages.push_back(new Word("sight with his strong hands."));
    _instructionPages[20]->setPosition(glm::vec2(10, 50));

    _instructionPages.push_back(new Word("CLIMBER"));
    _instructionPages[21]->setPosition(glm::vec2(10, 90));

    _instructionPages.push_back(new Word("His destiny is to defy the"));
    _instructionPages[22]->setPosition(glm::vec2(10, 110));

    _instructionPages.push_back(new Word("laws of the gravity. GG"));
    _instructionPages[23]->setPosition(glm::vec2(10, 130));


    _instructionPages.push_back(new Word("FLOATER"));
    _instructionPages[24]->setPosition(glm::vec2(10, 10));

    _instructionPages.push_back(new Word("Unlike FALLER, he will not"));
    _instructionPages[25]->setPosition(glm::vec2(10, 30));

    _instructionPages.push_back(new Word("die from falling."));
    _instructionPages[26]->setPosition(glm::vec2(10, 50));

    _instructionPages.push_back(new Word("BOMBER"));
    _instructionPages[27]->setPosition(glm::vec2(10, 90));

    _instructionPages.push_back(new Word("He likes explosions. A lot."));
    _instructionPages[28]->setPosition(glm::vec2(10, 110));

    _instructionPages.push_back(new Word("KABOOM!"));
    _instructionPages[29]->setPosition(glm::vec2(10, 130));


    _instructionPages.push_back(new Word("BUILDER"));
    _instructionPages[30]->setPosition(glm::vec2(10, 10));

    _instructionPages.push_back(new Word("He builds stairs to help"));
    _instructionPages[31]->setPosition(glm::vec2(10, 30));

    _instructionPages.push_back(new Word("other Lemmings to go on."));
    _instructionPages[32]->setPosition(glm::vec2(10, 50));

    _instructionPages.push_back(new Word("DIGGER"));
    _instructionPages[33]->setPosition(glm::vec2(10, 90));

    _instructionPages.push_back(new Word("He will eventually arrive"));
    _instructionPages[34]->setPosition(glm::vec2(10, 110));

    _instructionPages.push_back(new Word("to the center of the earth."));
    _instructionPages[35]->setPosition(glm::vec2(10, 130));


    _instructionPages.push_back(new Word("BASHER"));
    _instructionPages[36]->setPosition(glm::vec2(10, 10));

    _instructionPages.push_back(new Word("He will clear the way"));
    _instructionPages[37]->setPosition(glm::vec2(10, 30));

    _instructionPages.push_back(new Word("in a straight line."));
    _instructionPages[38]->setPosition(glm::vec2(10, 50));

    _instructionPages.push_back(new Word("MINER"));
    _instructionPages[39]->setPosition(glm::vec2(10, 90));

    _instructionPages.push_back(new Word("He is looking for gold"));
    _instructionPages[40]->setPosition(glm::vec2(10, 110));

    _instructionPages.push_back(new Word("in a diagonal direction."));
    _instructionPages[41]->setPosition(glm::vec2(10, 130));


    _instructionPages.push_back(new Word("Finally, if you feel confident"));
    _instructionPages[42]->setPosition(glm::vec2(10, 10));

    _instructionPages.push_back(new Word("enough you can activate hard"));
    _instructionPages[43]->setPosition(glm::vec2(10, 30));

    _instructionPages.push_back(new Word("mode by pressing H in the"));
    _instructionPages[44]->setPosition(glm::vec2(10, 50));

    _instructionPages.push_back(new Word("MENU. You will notice that"));
    _instructionPages[45]->setPosition(glm::vec2(10, 70));

    _instructionPages.push_back(new Word("HARD MODE is active seeing a"));
    _instructionPages[46]->setPosition(glm::vec2(10, 90));

    _instructionPages.push_back(new Word("skull in the top right corner."));
    _instructionPages[47]->setPosition(glm::vec2(10, 110));


    _instructionPages.push_back(new Word("In hard mode the map"));
    _instructionPages[48]->setPosition(glm::vec2(10, 10));

    _instructionPages.push_back(new Word("regenerates itself over time,"));
    _instructionPages[49]->setPosition(glm::vec2(10, 30));

    _instructionPages.push_back(new Word("so be carefull!"));
    _instructionPages[50]->setPosition(glm::vec2(10, 50));

    _instructionPages.push_back(new Word(""));
    _instructionPages[51]->setPosition(glm::vec2(10, 90));

    _instructionPages.push_back(new Word(""));
    _instructionPages[52]->setPosition(glm::vec2(10, 110));

    _instructionPages.push_back(new Word(""));
    _instructionPages[53]->setPosition(glm::vec2(10, 130));
}

void Instructions::endMusic() {
    _channel->stop();
}