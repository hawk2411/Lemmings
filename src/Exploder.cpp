#include "Exploder.h"
#include "Game.h"
#include "Scene.h"
#include "Utils.h"
#include "ParticleSystemManager.h"
#include "LevelRunner.h"

enum ExploderAnims {
    EXPLODER,
    BURNING_DEATH
};

Exploder::Exploder() : Job(Jobs::EXPLODER) {

}

void Exploder::initAnims(ShaderProgram &shaderProgram) {

    _jobSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f / 16, 1.f / 14), &shaderProgram,
                                      &Game::spriteSheets().lemmingAnimations,
                                      &Game::spriteSheets().rotatedLemmingAnimations);
    _jobSprite->setNumberAnimations(2);

    // EXPLODER

    _jobSprite->setAnimationSpeed(EXPLODER, 12);
    for (int i = 0; i < 16; i++) {
        _jobSprite->addKeyframe(EXPLODER, glm::vec2(float(i) / 16, 10.0f / 14));
    }

    // BURNING_DEATH
    _jobSprite->setAnimationSpeed(BURNING_DEATH, 12);
    for (int i = 0; i < 16; i++) {
        _jobSprite->addKeyframe(BURNING_DEATH, glm::vec2(float(i) / 16, 13.0f / 14));
    }


    state = EXPLODER_STATE;
    _jobSprite->changeAnimation(EXPLODER);

}

void Exploder::setWalkingRight(bool value) {
    walkingRight = value;
}

void Exploder::updateStateMachine(int deltaTime, Level *levelAttributes, IMaskManager *mask) {

    switch (state) {
        case EXPLODER_STATE:
            if (_jobSprite->isInLastFrame()) {
                state = BURNING_DEATH_STATE;
                _jobSprite->changeAnimation(BURNING_DEATH);
            }
            break;
        case BURNING_DEATH_STATE:
            if (_jobSprite->isInLastFrame()) {
                explode(nullptr);
                isFinished = true;
                _nextJob = Jobs::UNKNOWN;
            }

            break;
    }
}

void Exploder::explode(IMaskManager *mask) {
    glm::vec2 posBase = _jobSprite->getPosition();

    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 22; ++j) {
            int offset;
            if (j >= 15) {
                offset = Utils::max(j - 17, 0);
            } else {
                offset = 15 - 2 * j;
            }
            if (i >= offset && i < 16 - offset) {
                int x = posBase.x + i;
                int y = posBase.y + j;
                mask->eraseSpecialMask(x, y);
            }
        }
    }
    posBase += glm::ivec2(8, 15);

    ParticleSystemManager::getInstance().createNewParticleSystem(posBase);
}





