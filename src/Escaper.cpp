#include <fmod_studio.h>
#include "Escaper.h"
#include "Game.h"
#include "Scene.h"
#include "SoundManager.h"


enum EscaperAnims {
    ESCAPING
};

Escaper::Escaper(SoundManager *soundManager) : Job(Jobs::ESCAPER, soundManager) {
    escapeEfect = make_unique<Sound>(soundManager, "sounds/lemmingsEffects/YIPPEE.WAV",
                                                                FMOD_DEFAULT | FMOD_CREATESTREAM | FMOD_UNIQUE);

}

void Escaper::initAnims(ShaderProgram &shaderProgram) {
    _jobSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f / 16, 1.f / 14), &shaderProgram,
                                      &Game::spriteSheets().lemmingAnimations,
                                      &Game::spriteSheets().rotatedLemmingAnimations);
    _jobSprite->setNumberAnimations(1);

    // ESCAPING
    _jobSprite->setAnimationSpeed(ESCAPING, 12);
    for (int i = 0; i < 7; i++)
        _jobSprite->addKeyframe(ESCAPING, glm::vec2(float(i + 1) / 16, 1.0f / 14));

    state = ESCAPING_STATE;
    _jobSprite->changeAnimation(ESCAPING);


    escapeEfect->playSound();
    escapeEfect->setVolume(0.8f);
}

void Escaper::setWalkingRight(bool value) {
    walkingRight = value;
}

void Escaper::updateStateMachine(int deltaTime, Level *levelAttributes, IMaskManager *mask) {

    switch (state) {
        case ESCAPING_STATE:

            if (_jobSprite->isInLastFrame()) {
                isFinished = true;
                _nextJob = Jobs::UNKNOWN;

            }
    }
}


