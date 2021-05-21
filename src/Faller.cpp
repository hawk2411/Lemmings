#include "Faller.h"
#include "Game.h"
#include "Scene.h"
#include "JobFactory.h"

enum FallerAnims {
    FALLING_RIGHT, FALLING_LEFT,
    FALLING_DEATH
};

#define FATAL_FALLING_DISTANCE 65

Faller::Faller() : Job(Jobs::FALLER),
                   state(FallerState::FALLING_RIGHT_STATE),
                   deathEffect(nullptr),
                   currentDistance(0),
                   dead(false) {
    deathEffect = make_unique<Sound>(Game::instance()->getSoundManager(), "sounds/lemmingsEffects/SPLAT.WAV",
                                     FMOD_DEFAULT | FMOD_CREATESTREAM | FMOD_UNIQUE);
}

Faller::~Faller() {
}

void Faller::initAnims(ShaderProgram &shaderProgram) {
    _jobSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f / 16, 1.f / 14), &shaderProgram,
                                      &Game::spriteSheets().lemmingAnimations,
                                      &Game::spriteSheets().rotatedLemmingAnimations);
    _jobSprite->setNumberAnimations(3);

    // FALLING
    _jobSprite->setAnimationSpeed(FALLING_RIGHT, 12);
    for (int i = 0; i < 4; i++)
        _jobSprite->addKeyframe(FALLING_RIGHT, glm::vec2(float(i) / 16, 2.0f / 14));

    _jobSprite->setAnimationSpeed(FALLING_LEFT, 12);
    for (int i = 0; i < 4; i++)
        _jobSprite->addKeyframe(FALLING_LEFT, glm::vec2((15 - float(i)) / 16, 2.0f / 14), true);


    // FALLING_DEATH
    _jobSprite->setAnimationSpeed(FALLING_DEATH, 12);
    for (int i = 0; i < 16; i++)
        _jobSprite->addKeyframe(FALLING_DEATH, glm::vec2(float(i) / 16, 11.0f / 14));

    state = FallerState::FALLING_RIGHT_STATE;
    _jobSprite->changeAnimation(FALLING_RIGHT);

}

void Faller::setWalkingRight(bool value) {
    walkingRight = value;

    if (walkingRight) {
        _jobSprite->changeAnimation(FALLING_RIGHT);
        state = FallerState::FALLING_RIGHT_STATE;
    } else {
        _jobSprite->changeAnimation(FALLING_LEFT);
        state = FallerState::FALLING_LEFT_STATE;
    }
}

void Faller::updateStateMachine(int deltaTime, Level *levelAttributes, IMaskManager *mask) {
    int fall;

    switch (state) {
        case FallerState::FALLING_LEFT_STATE:
        case FallerState::FALLING_RIGHT_STATE:
            fall = collisionFloor(3, levelAttributes->maskedMap);
            if (fall > 0) {
                _jobSprite->incPosition(glm::vec2(0, fall));
                currentDistance += fall;
                if (currentDistance >= FATAL_FALLING_DISTANCE) {
                    cout << "Faller fatal falling distance" << endl;
                    dead = true;
                }
            } else {
                if (dead) {
                    state = FallerState::FALLING_DEATH_STATE;
                    _jobSprite->changeAnimation(FALLING_DEATH);
                    deathEffect->playSound();
                    deathEffect->setVolume(0.8f);
                } else {
                    isFinished = true;
                    _nextJob = Jobs::WALKER;
                }
            }
            break;

        case FallerState::FALLING_DEATH_STATE:
            if (_jobSprite->isInLastFrame()) {
                isFinished = true;
                if (_nextJob != Jobs::UNKNOWN) {
                    _nextJob = Jobs::UNKNOWN;
                }
            }
            break;
    }
}









