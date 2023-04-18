#include "Digger.h"
#include "Game.h"




void Digger::initAnimations(ShaderProgram &shaderProgram) {
    _jobSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f / 16, 1.f / 14), &shaderProgram,
                                      &Game::spriteSheets().lemmingAnimations,
                                      &Game::spriteSheets().rotatedLemmingAnimations);
    _jobSprite->setNumberAnimations(1);

    // DIGGER
    _jobSprite->setAnimationSpeed(0, 12);
    for (int i = 0; i < 8; i++)
        _jobSprite->addKeyframe(0, glm::vec2(float(i) / 16, 8.0f / 14));


    _jobSprite->changeAnimation(0);
}

void Digger::setWalkingRight(bool value) {
    _walkingRight = value;
}

void Digger::updateStateMachine(int deltaTime, Level *levelAttributes, IMaskManager *mask) {

    if (!canDig(mask)) {
        _isFinished = true;

        int fall = collisionFloor(DEFAULT_MAX_FALL, levelAttributes->maskedMap);
        if (fall >= DEFAULT_MAX_FALL) {
            _nextJob = Jobs::FALLER;
        } else {
            _nextJob = Jobs::WALKER;
        }
    } else if (_jobSprite->isInFirstFrame() || _jobSprite->getAnimationCurrentFrame() == 4) {
        dig(mask);
    }

}

bool Digger::canDig(IMaskManager *mask) const {
    glm::ivec2 posBase = _jobSprite->getPosition();

    posBase += glm::ivec2(4, 14);
    for (int j = 0; j < 3; ++j) {
        for (int i = 0; i < 9; ++i) {
            int x = posBase.x + i;
            int y = posBase.y + j;
            if (mask->isPositionABorder(x, y)) {
                return true;
            }
        }
    }
    return false;
}

void Digger::dig(IMaskManager *mask) {

    glm::ivec2 posBase = _jobSprite->getPosition();

    posBase += glm::ivec2(4, 14);

    int y = posBase.y;

    for (int i = 0; i < 9; ++i) {
        int x = posBase.x + i;
        mask->eraseMask(x, y, 0);
    }

    _jobSprite->incPosition(glm::ivec2(0, 1));
}








