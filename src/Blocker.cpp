#include "Blocker.h"
#include "Game.h"

Blocker::Blocker() : Job(Jobs::BLOCKER), _state(BlockerState::BLOCKING_STATE) {

}

void Blocker::initAnims(ShaderProgram &shaderProgram) {
    _jobSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f / 16, 1.f / 14), &shaderProgram,
                                      &Game::spriteSheets().lemmingAnimations,
                                      &Game::spriteSheets().rotatedLemmingAnimations);
    _jobSprite->setNumberAnimations(1);

    // BLOCKER
    _jobSprite->setAnimationSpeed(0, 12);
    for (int i = 0; i < 16; i++)
        _jobSprite->addKeyframe(0, glm::vec2(float(i) / 16, 3.0f / 14));

    _state = BlockerState::BLOCKING_STATE;
    _jobSprite->changeAnimation(0);

}

void Blocker::setWalkingRight(bool value) {
    _walkingRight = value;
}

void Blocker::updateStateMachine(int deltaTime, Level *levelAttributes, IMaskManager *mask) {

    switch (_state) {
        case BlockerState::BLOCKING_STATE:

            glm::ivec2 posBase = _jobSprite->getPosition();

            posBase += glm::ivec2(3, 1);

            int x = posBase.x;
            int y = posBase.y;

            for (int i = 0; i < 10; i += 9) {
                for (int j = 0; j < 16; ++j) {
                    mask->applySpecialMask(x + i, y + j);
                }
            }

            break;
    }
}

