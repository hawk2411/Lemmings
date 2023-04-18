#include "Miner.h"
#include "Game.h"
#include "Utils.h"

enum MinerAnims {
    MINER_RIGHT, MINER_LEFT
};

Miner::Miner() : Job(Jobs::MINER), _state(MINER_RIGHT_STATE) {

}

void Miner::initAnimations(ShaderProgram &shaderProgram) {
    _jobSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f / 16, 1.f / 14), &shaderProgram,
                                      &Game::spriteSheets().lemmingAnimations,
                                      &Game::spriteSheets().rotatedLemmingAnimations);
    _jobSprite->setNumberAnimations(2);


    // MINER
    _jobSprite->setAnimationSpeed(MINER_RIGHT, 12);
    for (int i = 0; i < 24; i++)
        if (i < 8) {
            _jobSprite->addKeyframe(MINER_RIGHT, glm::vec2(float(i + 8) / 16, 8.0f / 14));
        } else {
            _jobSprite->addKeyframe(MINER_RIGHT, glm::vec2(float(i - 8) / 16, 9.0f / 14));
        }

    _jobSprite->setAnimationSpeed(MINER_LEFT, 12);
    for (int i = 0; i < 24; i++)
        if (i < 8) {
            _jobSprite->addKeyframe(MINER_LEFT, glm::vec2((15 - float(i + 8)) / 16, 8.0f / 14), true);
        } else {
            _jobSprite->addKeyframe(MINER_LEFT, glm::vec2(((23 - float(i)) / 16), 9.0f / 14), true);
        }

    _state = MINER_RIGHT_STATE;
    _jobSprite->changeAnimation(MINER_RIGHT);


}

void Miner::setWalkingRight(bool value) {
    _walkingRight = value;

    if (_walkingRight) {
        _state = MINER_RIGHT_STATE;
        _jobSprite->changeAnimation(MINER_RIGHT);
    } else {
        _state = MINER_LEFT_STATE;
        _jobSprite->changeAnimation(MINER_LEFT);
    }
}

void Miner::updateStateMachine(int deltaTime, Level *levelAttributes, IMaskManager *mask) {

    if(!_minerStates[_state]->canMine(this, mask)) {
        _isFinished = true;
        int fall = collisionFloor(DEFAULT_MAX_FALL, levelAttributes->maskedMap);
        _nextJob = (fall >= 3) ? Jobs::FALLER : Jobs::WALKER;

    } else {
        _minerStates[_state]->doMine(this, mask);
    }
}


void Miner::MinerRight::doMine(Job *job, IMaskManager *maskManager) {
    //printMine();
    glm::ivec2 posBase = job->sprite()->getPosition();

    posBase += glm::ivec2(10, 16);

    if (job->sprite()->getAnimationCurrentFrame() == 2) {
        int x = posBase.x;
        int y = posBase.y;

        for (int i = 0; i < 4; ++i) {
            maskManager->eraseMask(x + i, y, 0);
            maskManager->eraseMask(x + i, y - (i + 1), 0);
            maskManager->eraseMask(x + i, y - (i + 2), 0);
            maskManager->eraseMask(x + i, y - 12, 0);
            maskManager->eraseMask(x + i, y - 11, 0);
            maskManager->eraseMask(x + i, y - 10, 0);
        }

        for (int i = 0; i < 12; ++i) {
            maskManager->eraseMask(x + 4, y - i, 0);
        }

        for (int i = 2; i < 11; ++i) {
            maskManager->eraseMask(x + 5, y - i, 0);
        }
    }
    if (job->sprite()->getAnimationCurrentFrame() == 17) {
        job->sprite()->incPosition(glm::vec2(2, 1));

    }

}

bool Miner::MinerRight::canMine(Job *job, IMaskManager *maskManager) {
    glm::ivec2 posBase = job->sprite()->getPosition();

    posBase += glm::ivec2(10, 17);

    int x = posBase.x;
    int y = posBase.y;

    for (int i = 0; i < 3; ++i) {
        if (maskManager->isPositionABorder(x + i, y)) {
            return true;
        }
        if (maskManager->isPositionABorder(x + i, y - (i + 1))) {
            return true;
        }
        if (maskManager->isPositionABorder(x + i, y - (i + 2))) {
            return true;
        }
        if (maskManager->isPositionABorder(x + i, y - 12)) {
            return true;
        }
        if (maskManager->isPositionABorder(x + i, y - 11)) {
            return true;
        }
        if (maskManager->isPositionABorder(x + i, y - 10)) {
            return true;
        }

    }

    for (int i = 0; i < 12; i += 11) {
        if (maskManager->isPositionABorder(x + 3, y - i)) {
            return true;
        }
        if (maskManager->isPositionABorder(x + 3, y - (i + 1))) {
            return true;
        }
    }

    for (int i = 1; i < 12; ++i) {
        if (maskManager->isPositionABorder(x + 4, y - i)) {
            return true;
        }
    }

    for (int i = 2; i < 11; ++i) {
        if (maskManager->isPositionABorder(x + 5, y - i)) {
            return true;
        }
    }

    return false;
}

bool Miner::MinerLeft::canMine(Job *job, IMaskManager *maskManager) {

    glm::ivec2 posBase = job->sprite()->getPosition();

    posBase += glm::ivec2(0, 17);

    int x = posBase.x;
    int y = posBase.y;

    for (int i = 1; i < 11; ++i) {
        if (maskManager->isPositionABorder(x, y - i) ) {
            return true;
        }
    }

    for (int i = 0; i < 12; ++i) {
        if (maskManager->isPositionABorder(x + 1, y - i)) {
            return true;
        }
    }

    for (int i = 0; i < 12; i += 11) {
        if (maskManager->isPositionABorder(x + 2, y - i)) {
            return true;
        }
        if (maskManager->isPositionABorder(x + 2, y - (i + 1))) {
            return true;
        }
    }

    for (int i = 2; i < 6; ++i) {
        for (int j = 0; j < 13; j += 12) {
            if (maskManager->isPositionABorder(x + i, y - j)) {
                return true;
            }

            if (maskManager->isPositionABorder(x + i, y - (j + 1))) {
                return true;
            }
        }
    }
    return false;
}

void Miner::MinerLeft::doMine(Job *job, IMaskManager *maskManager) {
    
    glm::ivec2 posBase = job->sprite()->getPosition();
    posBase += glm::ivec2(0, 16);

    if (job->sprite()->getAnimationCurrentFrame() == 2) {
        int x = posBase.x;
        int y = posBase.y;

        for (int i = 1; i < 11; ++i) {
            maskManager->eraseMask(x, y - i, 0);
        }

        for (int i = 0; i < 12; ++i) {
            maskManager->eraseMask(x + 1, y - i, 0);
        }

        for (int i = 0; i < 12; i += 11) {
            maskManager->eraseMask(x + 2, y - i, 0);
            maskManager->eraseMask(x + 2, y - (i + 1), 0);
        }

        for (int i = 2; i < 6; ++i) {
            for (int j = 0; j < 13; j += 12) {
                maskManager->eraseMask(x + i, y - j, 0);
                maskManager->eraseMask(x + i, y - (j + 1), 0);
            }
        }
    }

    if (job->sprite()->getAnimationCurrentFrame() == 17) {
        job->sprite()->incPosition(glm::vec2(-2, 1));

    }

}
