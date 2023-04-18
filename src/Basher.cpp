#include "Basher.h"
#include "Game.h"
#include "Utils.h"

enum BasherAnimations {
    BASHER_RIGHT, BASHER_LEFT
};

Basher::Basher() : Job(Jobs::BASHER) {}

void Basher::initAnimations(ShaderProgram &shaderProgram) {
    _jobSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f / 16, 1.f / 14), &shaderProgram,
                                      &Game::spriteSheets().lemmingAnimations,
                                      &Game::spriteSheets().rotatedLemmingAnimations);
    _jobSprite->setNumberAnimations(2);

    // BASHER
    _jobSprite->setAnimationSpeed(BASHER_RIGHT, 12);
    for (int i = 0; i < 32; i++) {
        _jobSprite->addKeyframe(BASHER_RIGHT,
                                glm::vec2(float(i % 16) / 16, (6.0f + static_cast<float >(i) / 16) / 14));
    }
    _jobSprite->setAnimationSpeed(BASHER_LEFT, 12);
    for (int i = 0; i < 32; i++) {
        _jobSprite->addKeyframe(BASHER_LEFT,
                                glm::vec2((15 - float(i % 16)) / 16,
                                          (6.0f + static_cast<float>(i) / 16) / 14), true);
    }

    _state = BASHING_RIGHT_STATE;
    _jobSprite->changeAnimation(BASHER_RIGHT);

}

void Basher::setWalkingRight(bool value) {
    _walkingRight = value;
    if (_walkingRight) {
        _jobSprite->changeAnimation(BASHER_RIGHT);
        _state = BASHING_RIGHT_STATE;
    } else {
        _jobSprite->changeAnimation(BASHER_LEFT);
        _state = BASHING_LEFT_STATE;
    }


}

void Basher::updateStateMachine(int deltaTime, Level *levelAttributes, IMaskManager *mask) {
    _bashStates[_state]->doBashing(this, mask, deltaTime);
}

bool Basher::BashingRight::doBashing(Job *job, IMaskManager *mask, int time)  {
    glm::ivec2 posBase = job->sprite()->getPosition();
    posBase += glm::ivec2(8, 16);
    int y = posBase.y;
    int x = posBase.x;

    bool canBash = false;
    for (int i = 0; i <= 6; ++i) {
        for (int j = 0; j <= 8; ++j) {
            canBash =mask->isPositionABorder(x + i, y - 1 - j);
        }
    }
    for (int i = 0; i <= 6; ++i) {
        canBash = mask->isPositionABorder(x + 7, y - 2 - i);
    }

    if (!canBash) {
        return false;
    }

    auto currentFrame = job->sprite()->getAnimationCurrentFrame();
    if (currentFrame == 2 || currentFrame == 18) {
        for (int i = 0; i <= 6; ++i) {
            for (int j = 0; j <= 8; ++j) {
                mask->eraseMask(x + i, y - 1 - j, time);
            }
        }

        for (int i = 0; i <= 6; ++i) {
            mask->eraseMask(x + 7, y - 2 - i, time);
        }
    }

    if (!((7 <= currentFrame && currentFrame <= 15) || (23 <= currentFrame && currentFrame <= 31))) {
        job->sprite()->incPosition(glm::vec2(1, 0));
    }

    return BasherStateCommon::doBashing(job, mask, time);
}


bool Basher::BashingLeft::doBashing(Job *job, IMaskManager *mask, int time) {
    glm::ivec2 posBase = job->sprite()->getPosition();
    posBase += glm::ivec2(7, 16);
    int y = posBase.y;
    int x = posBase.x;

    bool canBash = false;
    for (int i = 0; i <= 6; ++i) {
        for (int j = 0; j <= 8; ++j) {
            canBash = mask->isPositionABorder(x - i, y - 1 - j);
        }
    }
    for (int i = 0; i <= 6; ++i) {
        canBash=  mask->isPositionABorder(x - 7, y - 2 - i);
    }

    if (!canBash) {
        return false;
    }

    auto currentFrame = job->sprite()->getAnimationCurrentFrame();
    if (currentFrame == 2 || currentFrame == 18) {
        for (int i = 0; i <= 6; ++i) {
            for (int j = 0; j <= 8; ++j) {
                mask->eraseMask(x - i, y - 1 - j, time);
            }
        }

        for (int i = 0; i <= 6; ++i) {
            mask->eraseMask(x - 7, y - 2 - i, time);
        }
    }

    if (!((7 <= currentFrame && currentFrame <= 15) || (23 <= currentFrame && currentFrame <= 31))) {
        job->sprite()->incPosition(glm::vec2(-1, 0));
    }

    return BasherStateCommon::doBashing(job, mask, time);
}







