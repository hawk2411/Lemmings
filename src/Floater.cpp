#include "Floater.h"
#include "Game.h"
#include "Scene.h"


enum FloaterAnims {
    WALKING_LEFT, WALKING_RIGHT,
    FALLING_RIGHT, FALLING_LEFT,
    FLOATER_OPENING_RIGHT, FLOATER_OPENING_LEFT, FLOATER_FALLING_RIGHT, FLOATER_FALLING_LEFT
};

Floater::Floater() : Job(Jobs::FLOATER) {

}

void Floater::initAnims(ShaderProgram &shaderProgram) {
    _jobSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f / 16, 1.f / 14), &shaderProgram,
                                      &Game::spriteSheets().lemmingAnimations,
                                      &Game::spriteSheets().rotatedLemmingAnimations);
    _jobSprite->setNumberAnimations(10);

    // WALKING
    _jobSprite->setAnimationSpeed(WALKING_RIGHT, 12);
    for (int i = 0; i < 8; i++) {
        _jobSprite->addKeyframe(WALKING_RIGHT, glm::vec2(float(i) / 16, 0.0f));
    }

    _jobSprite->setAnimationSpeed(WALKING_LEFT, 12);
    for (int i = 0; i < 8; i++) {
        _jobSprite->addKeyframe(WALKING_LEFT, glm::vec2((15 - float(i)) / 16, 0.0f), true);
    }

    // FALLING
    _jobSprite->setAnimationSpeed(FALLING_RIGHT, 12);
    for (int i = 0; i < 4; i++)
        _jobSprite->addKeyframe(FALLING_RIGHT, glm::vec2(float(i) / 16, 2.0f / 14));

    _jobSprite->setAnimationSpeed(FALLING_LEFT, 12);
    for (int i = 0; i < 4; i++)
        _jobSprite->addKeyframe(FALLING_LEFT, glm::vec2((15 - float(i)) / 16, 2.0f / 14), true);

    // FLOATER

    _jobSprite->setAnimationSpeed(FLOATER_OPENING_RIGHT, 12);
    for (int i = 0; i < 4; i++)
        _jobSprite->addKeyframe(FLOATER_OPENING_RIGHT, glm::vec2(float(i + 4) / 16, 2.0f / 14));

    _jobSprite->setAnimationSpeed(FLOATER_OPENING_LEFT, 12);
    for (int i = 0; i < 4; i++)
        _jobSprite->addKeyframe(FLOATER_OPENING_LEFT, glm::vec2((15 - float(i + 4)) / 16, 2.0f / 14), true);

    _jobSprite->setAnimationSpeed(FLOATER_FALLING_RIGHT, 12);
    for (int i = 0; i < 4; i++)
        _jobSprite->addKeyframe(FLOATER_FALLING_RIGHT, glm::vec2(float(i + 8) / 16, 2.0f / 14));

    _jobSprite->setAnimationSpeed(FLOATER_FALLING_LEFT, 12);
    for (int i = 0; i < 4; i++)
        _jobSprite->addKeyframe(FLOATER_FALLING_LEFT, glm::vec2((15 - float(i + 8)) / 16, 2.0f / 14), true);


    state = WALKING_RIGHT_STATE;
    _jobSprite->changeAnimation(WALKING_RIGHT);

}

void Floater::updateStateMachine(int deltaTime, Level *levelAttributes, IMaskManager *mask) {
    int fall;

    switch (state) {
        case WALKING_LEFT_STATE:
            _jobSprite->incPosition(glm::vec2(-1, -1));

            if (collision(levelAttributes->maskedMap)) {
                _jobSprite->decPosition(glm::vec2(-1, -1));
                walkingRight = true;
                _jobSprite->changeAnimation(WALKING_RIGHT);
                state = WALKING_RIGHT_STATE;
            } else {
                fall = collisionFloor(3, levelAttributes->maskedMap);
                if (fall > 0) {
                    _jobSprite->incPosition(glm::vec2(0, 1));
                }
                if (fall > 1) {
                    _jobSprite->incPosition(glm::vec2(0, 1));
                }

                if (fall > 2) {
                    _jobSprite->changeAnimation(FALLING_LEFT);
                    state = FALLING_LEFT_STATE;
                } else {
                    if (_jobSprite->getPosition() ==
                        levelAttributes->_door->getEscapePosition()) {
                        isFinished = true;
                        _nextJob = Jobs::ESCAPER;
                    }
                }
            }
            break;

        case WALKING_RIGHT_STATE:
            _jobSprite->incPosition(glm::vec2(1, -1));

            if (collision(levelAttributes->maskedMap)) {
                _jobSprite->decPosition(glm::vec2(1, -1));
                walkingRight = false;
                _jobSprite->changeAnimation(WALKING_LEFT);
                state = WALKING_LEFT_STATE;
            } else {
                fall = collisionFloor(3, levelAttributes->maskedMap);
                if (fall < 3) {
                    _jobSprite->incPosition(glm::vec2(0, fall));

                    if (_jobSprite->getPosition() ==
                        levelAttributes->_door->getEscapePosition()) {
                        isFinished = true;
                        _nextJob = Jobs::ESCAPER;
                    }
                } else {
                    _jobSprite->changeAnimation(FALLING_RIGHT);
                    state = FALLING_RIGHT_STATE;
                }

            }
            break;

        case FALLING_LEFT_STATE:
            if (_jobSprite->isInLastFrame()) {
                _jobSprite->changeAnimation(FLOATER_OPENING_LEFT);
                state = FLOATER_OPENING_LEFT_STATE;
            } else {
                fall = collisionFloor(2, levelAttributes->maskedMap);
                if (fall > 0) {
                    _jobSprite->incPosition(glm::vec2(0, fall));
                }
            }
            break;
        case FALLING_RIGHT_STATE:
            if (_jobSprite->isInLastFrame()) {
                _jobSprite->changeAnimation(FLOATER_OPENING_RIGHT);
                state = FLOATER_OPENING_RIGHT_STATE;
            } else {
                fall = collisionFloor(2, levelAttributes->maskedMap);
                if (fall > 0) {
                    _jobSprite->incPosition(glm::vec2(0, fall));
                }
            }
            break;

        case FLOATER_OPENING_LEFT_STATE:
            if (_jobSprite->hasIterated()) {
                _jobSprite->changeAnimation(FLOATER_FALLING_LEFT);
                state = FLOTATING_LEFT_STATE;
            }
            break;

        case FLOATER_OPENING_RIGHT_STATE:
            if (_jobSprite->hasIterated()) {
                _jobSprite->changeAnimation(FLOATER_FALLING_RIGHT);
                state = FLOTATING_RIGHT_STATE;
            }
            break;

        case FLOTATING_LEFT_STATE:
            fall = collisionFloor(2, levelAttributes->maskedMap);
            if (fall > 0)
                _jobSprite->incPosition(glm::vec2(0, fall));
            else {
                _jobSprite->changeAnimation(WALKING_LEFT);
                state = WALKING_LEFT_STATE;
            }
            break;

        case FLOTATING_RIGHT_STATE:
            fall = collisionFloor(2, levelAttributes->maskedMap);
            if (fall > 0)
                _jobSprite->incPosition(glm::vec2(0, fall));
            else {
                _jobSprite->changeAnimation(WALKING_RIGHT);
                state = WALKING_RIGHT_STATE;
            }
            break;

    }
}

//void Floater::timeToFloat()const {
//    glm::ivec2 posBase = _jobSprite->getPosition();
//
//    posBase += glm::ivec2(5, 16);
//
//    int y = posBase.y;
//
//    for (int i = 0; i < 7; ++i) {
//        int x = posBase.x + i;
//        Scene::getInstance().eraseMask(x, y, 0);
//    }
//    _jobSprite->incPosition(glm::vec2(0, -1));
//}


void Floater::setWalkingRight(bool value) {
    walkingRight = value;
    if (walkingRight) {
        _jobSprite->changeAnimation(WALKING_RIGHT);
        state = WALKING_RIGHT_STATE;
    } else {
        _jobSprite->changeAnimation(WALKING_LEFT);
        state = WALKING_LEFT_STATE;
    }
    return;
}




