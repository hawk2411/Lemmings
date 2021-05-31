#include "Climber.h"
#include "Game.h"


enum ClimberAnims {
    WALKING_LEFT, WALKING_RIGHT,
    CLIMBING_LEFT, CLIMBING_RIGHT,
    LEDGING_LEFT, LEDGING_RIGHT
};

Climber::Climber() : Job(Jobs::CLIMBER) {
    state = CLIMBING_RIGHT_STATE;
}


void Climber::initAnims(ShaderProgram &shaderProgram) {
    _jobSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f / 16, 1.f / 14), &shaderProgram,
                                      &Game::spriteSheets().lemmingAnimations,
                                      &Game::spriteSheets().rotatedLemmingAnimations);
    _jobSprite->setNumberAnimations(6);

    // CLIMBER
    _jobSprite->setAnimationSpeed(CLIMBING_RIGHT, 12);
    for (int i = 0; i < 8; i++)
        _jobSprite->addKeyframe(CLIMBING_RIGHT, glm::vec2(float(i) / 16, 4.0f / 14));

    _jobSprite->setAnimationSpeed(CLIMBING_LEFT, 12);
    for (int i = 0; i < 8; i++)
        _jobSprite->addKeyframe(CLIMBING_LEFT, glm::vec2(float(15 - i) / 16, 4.0f / 14), true);

    _jobSprite->setAnimationSpeed(LEDGING_RIGHT, 12);
    for (int i = 0; i < 8; i++)
        _jobSprite->addKeyframe(LEDGING_RIGHT, glm::vec2(float(i + 8) / 16, 4.0f / 14));

    _jobSprite->setAnimationSpeed(LEDGING_LEFT, 12);
    for (int i = 0; i < 8; i++)
        _jobSprite->addKeyframe(LEDGING_LEFT, glm::vec2(float(7 - i) / 16, 4.0f / 14), true);

    // WALKING
    _jobSprite->setAnimationSpeed(WALKING_RIGHT, 12);
    for (int i = 0; i < 8; i++) {
        _jobSprite->addKeyframe(WALKING_RIGHT, glm::vec2(float(i) / 16, 0.0f));
    }

    _jobSprite->setAnimationSpeed(WALKING_LEFT, 12);
    for (int i = 0; i < 8; i++) {
        _jobSprite->addKeyframe(WALKING_LEFT, glm::vec2(float(15 - i) / 16, 0.0f), true);
    }

}

void Climber::setWalkingRight(bool value) {
    walkingRight = value;

    if (walkingRight) {
        _jobSprite->changeAnimation(WALKING_RIGHT);
        state = WALKING_RIGHT_STATE;
    } else {
        _jobSprite->changeAnimation(WALKING_LEFT);
        state = WALKING_LEFT_STATE;
    }
}

void Climber::updateStateMachine(int deltaTime, Level *levelAttributes, IMaskManager *mask) {
    int fall;

    switch (state) {
        case WALKING_LEFT_STATE:
            _jobSprite->incPosition(glm::vec2(-1, -1));

            if (collision(levelAttributes->maskedMap)) {
                _jobSprite->decPosition(glm::vec2(-1, -1));
                _jobSprite->changeAnimation(CLIMBING_LEFT);
                state = CLIMBING_LEFT_STATE;
            } else {
                fall = collisionFloor(3, levelAttributes->maskedMap);
                if (fall > 0) {
                    _jobSprite->incPosition(glm::vec2(0, 1));
                }
                if (fall > 1) {
                    _jobSprite->incPosition(glm::vec2(0, 1));
                }

                if (fall > 2) {

                    isFinished = true;
                    _nextJob = Jobs::FALLER;
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
                _jobSprite->changeAnimation(CLIMBING_RIGHT);
                state = CLIMBING_RIGHT_STATE;

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
                    isFinished = true;
                    _nextJob = Jobs::FALLER;
                }

            }
            break;
        case CLIMBING_LEFT_STATE:
            climbLeft(levelAttributes);
            break;
        case CLIMBING_RIGHT_STATE:
            climbRight(levelAttributes);
            break;
        case LEDGING_LEFT_STATE:
            if (_jobSprite->isInLastFrame()) {
                _jobSprite->incPosition(glm::vec2(-2, -3));
                _jobSprite->changeAnimation(WALKING_LEFT);
                state = WALKING_LEFT_STATE;
            }
            break;
        case LEDGING_RIGHT_STATE:
            if (_jobSprite->hasIterated()) {
                _jobSprite->incPosition(glm::vec2(3, -3));
                _jobSprite->changeAnimation(WALKING_RIGHT);
                state = WALKING_RIGHT_STATE;
            }
            break;

    }
}

void Climber::climbLeft(Level *level) {
    glm::vec2 posBase = _jobSprite->decPosition(glm::vec2(0, 1));


    posBase += glm::vec2(7, 15);

    if (level->maskedMap.pixel(static_cast<int>(_jobSprite->getPosition().x) + 7,
                               static_cast<int>(_jobSprite->getPosition().y) + 1) != 0) {
        _jobSprite->incPosition(glm::vec2(2, 0));
        isFinished = true;
        _nextJob = Jobs::FALLER;
    } else if (level->maskedMap.pixel(static_cast<int>(posBase.x) - 1, static_cast<int>(posBase.y) - 3) == 0) {
        _jobSprite->changeAnimation(LEDGING_LEFT);
        state = LEDGING_LEFT_STATE;

    }

}

void Climber::climbRight(Level *level) {
    glm::vec2 posBase = _jobSprite->decPosition(glm::vec2(0, 1));


    posBase += glm::vec2(8, 15);
    if (level->maskedMap.pixel(static_cast<int>(_jobSprite->getPosition().x) + 8,
                               static_cast<int>(_jobSprite->getPosition().y) + 1) != 0) {
        _jobSprite->incPosition(glm::vec2(-2, 0));
        isFinished = true;
        _nextJob = Jobs::FALLER;
    } else if (level->maskedMap.pixel(static_cast<int>(posBase.x) + 1, static_cast<int>(posBase.y) - 3) == 0) {
        _jobSprite->changeAnimation(LEDGING_RIGHT);
        state = LEDGING_RIGHT_STATE;
    }
}
