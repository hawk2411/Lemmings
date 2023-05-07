#include "Walker.h"
#include "Game.h"

enum WalkerAnims {
    WALKING_LEFT, WALKING_RIGHT
};

Walker::Walker() : Job(Jobs::WALKER), _state(WALKING_RIGHT_STATE) {}

void Walker::initAnimations(ShaderProgram &shaderProgram) {
    _jobSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f / 16, 1.f / 14), &shaderProgram,
                                      &Game::spriteSheets().lemmingAnimations,
                                      &Game::spriteSheets().rotatedLemmingAnimations);
    _jobSprite->setNumberAnimations(2);

    // WALKING
    _jobSprite->setAnimationSpeed(WALKING_RIGHT, default_animation_speed);
    for (int i = 0; i < 8; i++) {
        _jobSprite->addKeyframe(WALKING_RIGHT, glm::vec2(float(i) / 16, 0.0f));
    }

    _jobSprite->setAnimationSpeed(WALKING_LEFT, default_animation_speed);
    for (int i = 0; i < 8; i++) {
        _jobSprite->addKeyframe(WALKING_LEFT, glm::vec2((15 - float(i)) / 16, 0.0f), true);
    }
}

void Walker::setWalkingRight(bool value) {
    _walkingRight = value;

    if (_walkingRight) {
        _jobSprite->changeAnimation(WALKING_RIGHT);
        _state = WALKING_RIGHT_STATE;
    } else {
        _jobSprite->changeAnimation(WALKING_LEFT);
        _state = WALKING_LEFT_STATE;
    }
}

void Walker::updateStateMachine(int deltaTime, Level *levelAttributes, IMaskManager *mask) {

    auto next_pos = glm::vec2((_state == WALKING_LEFT_STATE) ? -1 : 1, -2);

    _jobSprite->incPosition(next_pos);
    if (collision(levelAttributes->maskedMap)) {
        _jobSprite->decPosition(next_pos);  //step back
        turn_around();
        return;
    }

    int fall = collisionFloor(DEFAULT_MAX_FALL + 1, levelAttributes->maskedMap);
    if (fall < DEFAULT_MAX_FALL + 1) {
        _jobSprite->incPosition(glm::vec2(0, fall));    //move down to the floor

        if (_jobSprite->getPosition() == levelAttributes->_door->getEscapePosition()) {
            _isFinished = true;
            _nextJob = Jobs::ESCAPER;
        }
    } else {
        _isFinished = true;
        _nextJob = Jobs::FALLER;
    }

}

void Walker::turn_around() {
    bool isWalkingLeft = (_state == WALKING_LEFT_STATE);
    _jobSprite->changeAnimation(isWalkingLeft ? WALKING_RIGHT : WALKING_LEFT);
    _state = isWalkingLeft ? WALKING_RIGHT_STATE : WALKING_LEFT_STATE;
    setWalkingRight(isWalkingLeft);
}







