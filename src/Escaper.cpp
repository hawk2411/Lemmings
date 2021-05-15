#include <fmod_studio.h>
#include "Escaper.h"
#include "Game.h"
#include "Scene.h"
#include "SoundManager.h"


enum EscaperAnims {
    ESCAPING
};

Escaper::Escaper(Jobs jobs) : Job(jobs) {
    escapeEfect = make_unique<Sound>(Game::instance().getSoundManager(), "sounds/lemmingsEffects/YIPPEE.WAV",
                                                                FMOD_DEFAULT | FMOD_CREATESTREAM | FMOD_UNIQUE);

}

void Escaper::initAnims(ShaderProgram &shaderProgram) {
    jobSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f / 16, 1.f / 14), &shaderProgram,
                                     &Game::spriteSheets().lemmingAnimations,
                                     &Game::spriteSheets().rotatedLemmingAnimations);
    jobSprite->setNumberAnimations(1);

    // ESCAPING
    jobSprite->setAnimationSpeed(ESCAPING, 12);
    for (int i = 0; i < 7; i++)
        jobSprite->addKeyframe(ESCAPING, glm::vec2(float(i + 1) / 16, 1.0f / 14));

    state = ESCAPING_STATE;
    jobSprite->changeAnimation(ESCAPING);


    escapeEfect->playSound();
    escapeEfect->setVolume(0.8f);
}

void Escaper::setWalkingRight(bool value) {
    walkingRight = value;
}

void Escaper::updateStateMachine(int deltaTime) {

    switch (state) {
        case ESCAPING_STATE:

            if (jobSprite->isInLastFrame()) {
                isFinished = true;
                _nextJob = Jobs::UNKNOWN;

            }
    }
}


