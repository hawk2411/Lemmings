#include "Builder.h"
#include "Game.h"
#include "ShaderManager.h"
#include "JobFactory.h"
#include "Utils.h"


enum BuilderAnims {
    BUILDING_LEFT, BUILDING_RIGHT,
    NOSTEPS
};

Builder::Builder() : Job(Jobs::BUILDER) {
    state = BUILDING_RIGHT_STATE;
}


void Builder::initAnims(ShaderProgram &shaderProgram) {
    _jobSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f / 16, 1.f / 14), &shaderProgram,
                                      &Game::spriteSheets().lemmingAnimations,
                                      &Game::spriteSheets().rotatedLemmingAnimations);
    _jobSprite->setNumberAnimations(3);

    // BUILDER
    _jobSprite->setAnimationSpeed(BUILDING_RIGHT, 12);
    for (int i = 0; i < 16; i++)
        _jobSprite->addKeyframe(BUILDING_RIGHT, glm::vec2(float(i) / 16, 5.0f / 14));

    _jobSprite->setAnimationSpeed(BUILDING_LEFT, 12);
    for (int i = 0; i < 16; i++)
        _jobSprite->addKeyframe(BUILDING_LEFT, glm::vec2(float(15 - i) / 16, 5.0f / 14), true);

    _jobSprite->setAnimationSpeed(NOSTEPS, 12);
    for (int i = 0; i < 6; i++)
        _jobSprite->addKeyframe(NOSTEPS, glm::vec2(float(10 + i) / 16, 0));


}

void Builder::setWalkingRight(bool value) {
    walkingRight = value;

    if (walkingRight) {
        _jobSprite->changeAnimation(BUILDING_RIGHT);
        state = BUILDING_RIGHT_STATE;
    } else {
        _jobSprite->changeAnimation(BUILDING_LEFT);
        state = BUILDING_LEFT_STATE;
    }
}

void Builder::updateStateMachine(int deltaTime, Level *levelAttributes, IMaskManager *mask) {
    int fall;

    switch (state) {
        case BUILDING_LEFT_STATE:
            if (cannotBuildLeft(mask)) {
                _jobSprite->changeAnimation(NOSTEPS);
                state = NOSTEPS_STATE;
            } else {
                buildLeft(levelAttributes, mask);
            }
            break;
        case BUILDING_RIGHT_STATE:
            if (cannotBuildRight(mask)) {
                _jobSprite->changeAnimation(NOSTEPS);
                state = NOSTEPS_STATE;

            } else {
                buildRight(levelAttributes, mask);
            }

            break;
        case NOSTEPS_STATE:
            if (_jobSprite->isInLastFrame()) {
                isFinished = true;
                _nextJob = Jobs::WALKER;
            }
            break;
    }
}

void Builder::buildLeft(Level *attributes, IMaskManager *mask) {
    if (_jobSprite->hasIterated()) {
        glm::vec2 posBase = _jobSprite->getPosition() + glm::vec2(3, 15);
        buildStep(posBase, attributes, mask);
        _jobSprite->incPosition(glm::vec2(-2, -1));
        ++buildedSteps;
        _jobSprite->setIterated(false);
    }
}

void Builder::buildRight(Level *attributes, IMaskManager *mask) {
    if (_jobSprite->hasIterated()) {
        glm::vec2 posBase = _jobSprite->getPosition() + glm::vec2(8, 15);
        buildStep(posBase, attributes, mask);
        _jobSprite->incPosition(glm::vec2(2, -1));
        ++buildedSteps;
        _jobSprite->setIterated(false);
    }
}

void Builder::buildStep(glm::vec2 position, Level* attributes, IMaskManager* mask) {
    for (int i = 0; i < 5; ++i) {
        Utils::changeTexelColor(attributes->levelTexture.getId(), position.x + i,
                                position.y, 120, 77, 0, 255);
        mask->applyMask(position.x + i, position.y);
    }
}

bool Builder::cannotBuildRight(IMaskManager *mask) {

    bool obtured = false;

    glm::vec2 posBase = _jobSprite->getPosition() + glm::vec2(9, 15);
    for (int i = 0; i < 4; ++i) {
        if (mask->getPixel(posBase.x + i, posBase.y) != 0) {
            obtured = true;
        }
    }
    return buildedSteps >= MAX_STEPS || obtured;
}

bool Builder::cannotBuildLeft(IMaskManager *mask) {

    bool obtured = false;

    glm::vec2 posBase = _jobSprite->getPosition() + glm::vec2(3, 15);
    for (int i = 0; i < 4; ++i) {
        if (mask->getPixel(posBase.x + i, posBase.y) != 0) {
            obtured = true;
        }
    }
    return buildedSteps >= MAX_STEPS || obtured;
}