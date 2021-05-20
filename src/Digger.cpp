#include "Digger.h"
#include "Game.h"
#include "Scene.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4

Digger::Digger() : Job(Jobs::DIGGER) {

}


void Digger::initAnims(ShaderProgram &shaderProgram) {
    _jobSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f / 16, 1.f / 14), &shaderProgram,
                                      &Game::spriteSheets().lemmingAnimations,
                                      &Game::spriteSheets().rotatedLemmingAnimations);
    _jobSprite->setNumberAnimations(1);

    // DIGGER
    _jobSprite->setAnimationSpeed(0, 12);
    for (int i = 0; i < 8; i++)
        _jobSprite->addKeyframe(0, glm::vec2(float(i) / 16, 8.0f / 14));


    state = DIGGING_STATE;
    _jobSprite->changeAnimation(0);
}

void Digger::setWalkingRight(bool value) {
    walkingRight = value;
}

void Digger::updateStateMachine(int deltaTime, Level *levelAttributes, IMaskManager *mask) {

    switch (state) {

        case DIGGING_STATE:
            if (!canDig()) {
                isFinished = true;

                int fall = collisionFloor(3);
                if (fall >= 3) {
                    _nextJob = Jobs::FALLER;;
                } else {
                    _nextJob = Jobs::WALKER;
                }
            } else if (_jobSprite->isInFirstFrame() || _jobSprite->getAnimationCurrentFrame() == 4) {
                dig();
            }

    }
}

bool Digger::canDig() const {
    glm::ivec2 posBase = _jobSprite->getPosition();

    posBase +=  glm::ivec2(4, 14);
    for (int j = 0; j < 3; ++j) {
        for (int i = 0; i < 9; ++i) {
            int x = posBase.x + i;
            int y = posBase.y + j;
            if (Scene::getInstance().getPixel(x, y) == -1) {
                return true;
            }
        }
    }
    return false;
}

void Digger::dig() {

    glm::ivec2 posBase = _jobSprite->getPosition();

    posBase += glm::ivec2(4, 14);

    int y = posBase.y;

    for (int i = 0; i < 9; ++i) {
        int x = posBase.x + i;
        Scene::getInstance().eraseMask(x, y);
    }

    _jobSprite->incPosition(glm::ivec2(0, 1));
}








