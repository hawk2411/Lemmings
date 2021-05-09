#include "Instructions.h"
#include "Utils.h"
#include "ShaderManager.h"
#include "InstructionsMouseManager.h"
#include "InstructionsKeyboardManager.h"
#include "KeyFactory.h"
#include "Game.h"

#define LINESPAGE 6

void Instructions::init() {
    currentTime = 0.0f;
    onlyRight = true;
    onlyLeft = false;
    actualPage = 0;
    initTextures();
    initSprites();
    mouseManager = &InstructionsMouseManager::getInstance();
    keyboardManager = &InstructionsKeyboardManager::getInstance();

    soundManager = Game::instance().getSoundManager();
    music = soundManager->loadSound("sounds/InstructionsSong.ogg", FMOD_LOOP_NORMAL | FMOD_CREATESTREAM);

    channel = soundManager->playSound(music);
    channel->setVolume(1.f);
}

void Instructions::update(int deltaTime) {
    currentTime += deltaTime;

}

void Instructions::render() {
    ShaderManager::getInstance().useShaderProgram();
    instructionsLevelSprite->render();
    for (int i = actualPage; i < Utils::min(actualPage + LINESPAGE, instructionPages.size()); ++i) {
        instructionPages[i]->render();
    }
    if (!onlyRight) {
        leftKey->render();
    }
    if (!onlyLeft) {
        rightKey->render();
    }

    instructionsWord->render();

    escapeKey->render();
}

void Instructions::initTextures() {
    instructionsLevelTexture.loadFromFile("images/menu/menuBackground.png", TEXTURE_PIXEL_FORMAT_RGBA);
    instructionsLevelTexture.setMinFilter(GL_NEAREST);
    instructionsLevelTexture.setMagFilter(GL_NEAREST);

}

void Instructions::initSprites() {

    leftKey = KeyFactory::instance().createLeftKey();
    leftKey->position() = glm::vec2(200, 160);

    instructionsWord = new Word("INSTRUCTIONS");
    instructionsWord->setPosition(glm::vec2(75, 170));

    rightKey = KeyFactory::instance().createRightKey();
    rightKey->position() = glm::vec2(230, 160);

    escapeKey = KeyFactory::instance().createEscapeKey();
    escapeKey->position() = glm::vec2(30, 160);

    instructionsLevelSprite = Sprite::createSprite(glm::vec2(CAMERA_WIDTH, CAMERA_HEIGHT), glm::vec2(1.f, 1.f),
                                                   &ShaderManager::getInstance().getShaderProgram(),
                                                   &instructionsLevelTexture);

    initLines();
}


void Instructions::passPageLeft() {
    if (actualPage - LINESPAGE >= 0) {
        actualPage -= LINESPAGE;
    }
    onlyRight = actualPage < LINESPAGE;
    onlyLeft = actualPage + LINESPAGE >= instructionPages.size();
}

void Instructions::passPageRight() {
    if (actualPage + LINESPAGE < instructionPages.size()) {
        actualPage += LINESPAGE;
    }

    onlyRight = actualPage < LINESPAGE;
    onlyLeft = actualPage + LINESPAGE >= instructionPages.size();
}

void Instructions::initLines() {
    instructionPages.clear();
    instructionPages.resize(0);

    instructionPages.push_back(new Word("Welcome to Lemmings!"));
    instructionPages[0]->setPosition(glm::vec2(10, 10));

    instructionPages.push_back(new Word("Your goal is to save as"));
    instructionPages[1]->setPosition(glm::vec2(10, 30));

    instructionPages.push_back(new Word("many Lemmings as possible."));
    instructionPages[2]->setPosition(glm::vec2(10, 50));

    instructionPages.push_back(new Word("In order to do that, assign"));
    instructionPages[3]->setPosition(glm::vec2(10, 80));

    instructionPages.push_back(new Word("JOBS to your Lemmings and get"));
    instructionPages[4]->setPosition(glm::vec2(10, 100));

    instructionPages.push_back(new Word("them to the level exit."));
    instructionPages[5]->setPosition(glm::vec2(10, 120));


    instructionPages.push_back(new Word("To assign jobs to Lemmings,"));
    instructionPages[6]->setPosition(glm::vec2(10, 10));

    instructionPages.push_back(new Word("just click in the"));
    instructionPages[7]->setPosition(glm::vec2(10, 30));

    instructionPages.push_back(new Word("corresponding button on"));
    instructionPages[8]->setPosition(glm::vec2(10, 50));

    instructionPages.push_back(new Word("the bottom of the screen"));
    instructionPages[9]->setPosition(glm::vec2(10, 70));

    instructionPages.push_back(new Word("and then click into a Lemming."));
    instructionPages[10]->setPosition(glm::vec2(10, 90));

    instructionPages.push_back(new Word("Next lets see all the jobs!"));
    instructionPages[11]->setPosition(glm::vec2(10, 130));


    instructionPages.push_back(new Word("WALKER"));
    instructionPages[12]->setPosition(glm::vec2(10, 10));

    instructionPages.push_back(new Word("The Walker is very simple:"));
    instructionPages[13]->setPosition(glm::vec2(10, 30));

    instructionPages.push_back(new Word("He walks."));
    instructionPages[14]->setPosition(glm::vec2(10, 50));

    instructionPages.push_back(new Word("FALLER"));
    instructionPages[15]->setPosition(glm::vec2(10, 90));

    instructionPages.push_back(new Word("His destiny is to follow the"));
    instructionPages[16]->setPosition(glm::vec2(10, 110));

    instructionPages.push_back(new Word("laws of the gravity. CAUTION!"));
    instructionPages[17]->setPosition(glm::vec2(10, 130));


    instructionPages.push_back(new Word("BLOCKER"));
    instructionPages[18]->setPosition(glm::vec2(10, 10));

    instructionPages.push_back(new Word("He will block every Lemming in"));
    instructionPages[19]->setPosition(glm::vec2(10, 30));

    instructionPages.push_back(new Word("sight with his strong hands."));
    instructionPages[20]->setPosition(glm::vec2(10, 50));

    instructionPages.push_back(new Word("CLIMBER"));
    instructionPages[21]->setPosition(glm::vec2(10, 90));

    instructionPages.push_back(new Word("His destiny is to defy the"));
    instructionPages[22]->setPosition(glm::vec2(10, 110));

    instructionPages.push_back(new Word("laws of the gravity. GG"));
    instructionPages[23]->setPosition(glm::vec2(10, 130));


    instructionPages.push_back(new Word("FLOATER"));
    instructionPages[24]->setPosition(glm::vec2(10, 10));

    instructionPages.push_back(new Word("Unlike FALLER, he will not"));
    instructionPages[25]->setPosition(glm::vec2(10, 30));

    instructionPages.push_back(new Word("die from falling."));
    instructionPages[26]->setPosition(glm::vec2(10, 50));

    instructionPages.push_back(new Word("BOMBER"));
    instructionPages[27]->setPosition(glm::vec2(10, 90));

    instructionPages.push_back(new Word("He likes explosions. A lot."));
    instructionPages[28]->setPosition(glm::vec2(10, 110));

    instructionPages.push_back(new Word("KABOOM!"));
    instructionPages[29]->setPosition(glm::vec2(10, 130));


    instructionPages.push_back(new Word("BUILDER"));
    instructionPages[30]->setPosition(glm::vec2(10, 10));

    instructionPages.push_back(new Word("He builds stairs to help"));
    instructionPages[31]->setPosition(glm::vec2(10, 30));

    instructionPages.push_back(new Word("other Lemmings to go on."));
    instructionPages[32]->setPosition(glm::vec2(10, 50));

    instructionPages.push_back(new Word("DIGGER"));
    instructionPages[33]->setPosition(glm::vec2(10, 90));

    instructionPages.push_back(new Word("He will eventually arrive"));
    instructionPages[34]->setPosition(glm::vec2(10, 110));

    instructionPages.push_back(new Word("to the center of the earth."));
    instructionPages[35]->setPosition(glm::vec2(10, 130));


    instructionPages.push_back(new Word("BASHER"));
    instructionPages[36]->setPosition(glm::vec2(10, 10));

    instructionPages.push_back(new Word("He will clear the way"));
    instructionPages[37]->setPosition(glm::vec2(10, 30));

    instructionPages.push_back(new Word("in a straight line."));
    instructionPages[38]->setPosition(glm::vec2(10, 50));

    instructionPages.push_back(new Word("MINER"));
    instructionPages[39]->setPosition(glm::vec2(10, 90));

    instructionPages.push_back(new Word("He is looking for gold"));
    instructionPages[40]->setPosition(glm::vec2(10, 110));

    instructionPages.push_back(new Word("in a diagonal direction."));
    instructionPages[41]->setPosition(glm::vec2(10, 130));


    instructionPages.push_back(new Word("Finally, if you feel confident"));
    instructionPages[42]->setPosition(glm::vec2(10, 10));

    instructionPages.push_back(new Word("enough you can activate hard"));
    instructionPages[43]->setPosition(glm::vec2(10, 30));

    instructionPages.push_back(new Word("mode by pressing H in the"));
    instructionPages[44]->setPosition(glm::vec2(10, 50));

    instructionPages.push_back(new Word("MENU. You will notice that"));
    instructionPages[45]->setPosition(glm::vec2(10, 70));

    instructionPages.push_back(new Word("HARD MODE is active seeing a"));
    instructionPages[46]->setPosition(glm::vec2(10, 90));

    instructionPages.push_back(new Word("skull in the top right corner."));
    instructionPages[47]->setPosition(glm::vec2(10, 110));


    instructionPages.push_back(new Word("In hard mode the map"));
    instructionPages[48]->setPosition(glm::vec2(10, 10));

    instructionPages.push_back(new Word("regenerates itself over time,"));
    instructionPages[49]->setPosition(glm::vec2(10, 30));

    instructionPages.push_back(new Word("so be carefull!"));
    instructionPages[50]->setPosition(glm::vec2(10, 50));

    instructionPages.push_back(new Word(""));
    instructionPages[51]->setPosition(glm::vec2(10, 90));

    instructionPages.push_back(new Word(""));
    instructionPages[52]->setPosition(glm::vec2(10, 110));

    instructionPages.push_back(new Word(""));
    instructionPages[53]->setPosition(glm::vec2(10, 130));
}

void Instructions::endMusic() {
    channel->stop();
}