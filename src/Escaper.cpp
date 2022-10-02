#include "common_defs.h"
#include "Escaper.h"
#include "Game.h"


enum EscaperAnims : std::size_t {
    ESCAPING = 0
};

Escaper::Escaper() : Job(Jobs::ESCAPER), escapeEffect_(createSound("sounds/lemmingsEffects/YIPPEE.WAV")), state(ESCAPING_STATE) {

}

void Escaper::initAnims(ShaderProgram &shaderProgram) {
    _jobSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f / LEMMINGS_PNG_COLUMNS, 1.f / LEMMINGS_PNG_ROWS), &shaderProgram,
                                      &Game::spriteSheets().lemmingAnimations,
                                      &Game::spriteSheets().rotatedLemmingAnimations);
    _jobSprite->setNumberAnimations(1);

    // ESCAPING
    _jobSprite->setAnimationSpeed(EscaperAnims::ESCAPING, 12);
    for (int i = 0; i < 7; i++)
        _jobSprite->addKeyframe(EscaperAnims::ESCAPING, glm::vec2(float(i + 1) / LEMMINGS_PNG_COLUMNS, 1.0f / LEMMINGS_PNG_ROWS));

    state = ESCAPING_STATE;
    _jobSprite->changeAnimation(EscaperAnims::ESCAPING);

    Mix_PlayChannel(-1, escapeEffect_.get(), 0);
    Mix_VolumeChunk(escapeEffect_.get(), MIX_MAX_VOLUME);
}

void Escaper::setWalkingRight(bool value) {
    _walkingRight = value;
}

void Escaper::updateStateMachine(int deltaTime, Level *levelAttributes, IMaskManager *mask) {

    switch (state) {
        case ESCAPING_STATE:

            if (_jobSprite->isInLastFrame()) {
                _isFinished = true;
                _nextJob = Jobs::UNKNOWN;

            }
    }
}


