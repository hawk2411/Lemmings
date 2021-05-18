#include "Walker.h"
#include "Game.h"
#include "Scene.h"

#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum WalkerAnims {
    WALKING_LEFT, WALKING_RIGHT
};

Walker::Walker() : Job(Jobs::WALKER), _state(WALKING_RIGHT_STATE){}

void Walker::initAnims(ShaderProgram &shaderProgram) {
    jobSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f / 16, 1.f / 14), &shaderProgram,
                                     &Game::spriteSheets().lemmingAnimations,
                                     &Game::spriteSheets().rotatedLemmingAnimations);
    jobSprite->setNumberAnimations(2);

    // WALKING
    jobSprite->setAnimationSpeed(WALKING_RIGHT, 12);
    for (int i = 0; i < 8; i++) {
        jobSprite->addKeyframe(WALKING_RIGHT, glm::vec2(float(i) / 16, 0.0f));
    }

    jobSprite->setAnimationSpeed(WALKING_LEFT, 12);
    for (int i = 0; i < 8; i++) {
        jobSprite->addKeyframe(WALKING_LEFT, glm::vec2((15 - float(i)) / 16, 0.0f), true);
    }
}

void Walker::setWalkingRight(bool value) {
    walkingRight = value;

    if (walkingRight) {
        jobSprite->changeAnimation(WALKING_RIGHT);
        _state = WALKING_RIGHT_STATE;
    } else {
        jobSprite->changeAnimation(WALKING_LEFT);
        _state = WALKING_LEFT_STATE;
    }
}

void Walker::updateStateMachine(int deltaTime) {
    int fall;

    switch (_state) {
        case WALKING_LEFT_STATE:
            jobSprite->incPosition(glm::vec2(-1, -2));

            if (collision()) {
                jobSprite->decPosition(glm::vec2(-1, -2));
                jobSprite->changeAnimation(WALKING_RIGHT);
                _state = WALKING_RIGHT_STATE;
                setWalkingRight(true);
            } else {
                fall = collisionFloor(4);
                if (fall < 4) {
                    jobSprite->incPosition( glm::vec2(0, fall));

                    if (jobSprite->getPosition() ==
                        Level::currentLevel().getLevelAttributes()->_door->getEscapePosition()) {
                        isFinished = true;
                        _nextJob = Jobs::ESCAPER;
                    }
                } else {
                    isFinished = true;
                    _nextJob = Jobs::FALLER;
                }
            }
            break;
        case WALKING_RIGHT_STATE:
            jobSprite->incPosition(glm::vec2(1, -2));

            if (collision()) {
                jobSprite->decPosition(glm::vec2(1, -2));
                jobSprite->changeAnimation(WALKING_LEFT);
                _state = WALKING_LEFT_STATE;
                setWalkingRight(false);

            } else {
                fall = collisionFloor(4);
                if (fall < 4) {
                    jobSprite->incPosition(glm::vec2(0, fall));

                    if (jobSprite->getPosition() ==
                        Level::currentLevel().getLevelAttributes()->_door->getEscapePosition()) {
                        isFinished = true;
                        _nextJob = Jobs::ESCAPER;
                    }
                } else {
                    isFinished = true;
                    _nextJob = Jobs::FALLER;
                }

            }
            break;
    }
}





