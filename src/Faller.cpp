#include "Faller.h"
#include "Game.h"
#include "Scene.h"
#include "JobFactory.h"

enum FallerAnims {
    FALLING_RIGHT, FALLING_LEFT,
    FALLING_DEATH
};

#define FATAL_FALLING_DISTANCE 65
Faller::Faller(Jobs jobs) : Job(jobs), state(FallerState::FALLING_RIGHT_STATE), deathEffect(nullptr)
{
    cout << "Faller job created" << endl;

}
Faller::~Faller() {
    cout << "Faller job deleted" << endl;
}

void Faller::initAnims(ShaderProgram &shaderProgram) {
    jobSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f / 16, 1.f / 14), &shaderProgram,
                                     &Game::spriteSheets().lemmingAnimations,
                                     &Game::spriteSheets().rotatedLemmingAnimations);
    jobSprite->setNumberAnimations(3);

    // FALLING
    jobSprite->setAnimationSpeed(FALLING_RIGHT, 12);
    for (int i = 0; i < 4; i++)
        jobSprite->addKeyframe(FALLING_RIGHT, glm::vec2(float(i) / 16, 2.0f / 14));

    jobSprite->setAnimationSpeed(FALLING_LEFT, 12);
    for (int i = 0; i < 4; i++)
        jobSprite->addKeyframe(FALLING_LEFT, glm::vec2((15 - float(i)) / 16, 2.0f / 14), true);


    // FALLING_DEATH
    jobSprite->setAnimationSpeed(FALLING_DEATH, 12);
    for (int i = 0; i < 16; i++)
        jobSprite->addKeyframe(FALLING_DEATH, glm::vec2(float(i) / 16, 11.0f / 14));

    state = FallerState::FALLING_RIGHT_STATE;
    jobSprite->changeAnimation(FALLING_RIGHT);

    deathEffect = Game::instance().getSoundManager()->loadSound("sounds/lemmingsEffects/SPLAT.WAV",
                                          FMOD_DEFAULT | FMOD_CREATESTREAM | FMOD_UNIQUE);

}

void Faller::setWalkingRight(bool value) {
    walkingRight = value;

    if (walkingRight) {
        jobSprite->changeAnimation(FALLING_RIGHT);
        state = FallerState::FALLING_RIGHT_STATE;
    } else {
        jobSprite->changeAnimation(FALLING_LEFT);
        state = FallerState::FALLING_LEFT_STATE;
    }
}

void Faller::updateStateMachine(int deltaTime) {
    int fall;

    switch (state) {
        case FallerState::FALLING_LEFT_STATE:
        case FallerState::FALLING_RIGHT_STATE:
            fall = collisionFloor(3);
            if (fall > 0) {
                cout << "Faller fall > 0" << endl;
                jobSprite->incPosition(glm::vec2(0, fall));
                currentDistance += fall;
                if (currentDistance >= FATAL_FALLING_DISTANCE) {
                    cout << "Faller fatal falling distance" << endl;
                    dead = true;
                }
            } else {
                if (dead) {
                    cout << "Faller is dead" << endl;
                    state = FallerState::FALLING_DEATH_STATE;
                    jobSprite->changeAnimation(FALLING_DEATH);
                    FMOD::Channel *channeled = Game::instance().getSoundManager()->playSound(deathEffect);
                    channeled->setVolume(0.8f);
                } else {
                    cout << "Faller is finished" << endl;
                    isFinished = true;
                    nextJob = JobFactory::instance().createWalkerJob();
                }
            }
            break;

        case FallerState::FALLING_DEATH_STATE:
            cout << "Faller FALLING_DEATH_STATE" << endl;
            if (jobSprite->isInLastFrame()) {
                isFinished = true;
                if(nextJob){
                    delete nextJob;
                    nextJob = nullptr;
                }

            }
            break;
    }
}









