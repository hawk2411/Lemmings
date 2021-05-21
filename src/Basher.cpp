#include "Basher.h"
#include "Game.h"
#include "Utils.h"

#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum BasherAnims {
    BASHER_RIGHT, BASHER_LEFT
};

Basher::Basher(SoundManager *soundManager) : Job(Jobs::BASHER, soundManager) {

}

void Basher::initAnims(ShaderProgram &shaderProgram) {
    _jobSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f / 16, 1.f / 14), &shaderProgram,
                                      &Game::spriteSheets().lemmingAnimations,
                                      &Game::spriteSheets().rotatedLemmingAnimations);
    _jobSprite->setNumberAnimations(2);

    // BASHER
    _jobSprite->setAnimationSpeed(BASHER_RIGHT, 12);
    for (int i = 0; i < 32; i++)
        _jobSprite->addKeyframe(BASHER_RIGHT, glm::vec2(float(i % 16) / 16, (6.0f + i / 16) / 14));
    _jobSprite->setAnimationSpeed(BASHER_LEFT, 12);
    for (int i = 0; i < 32; i++)
        _jobSprite->addKeyframe(BASHER_LEFT, glm::vec2((15 - float(i % 16)) / 16, (6.0f + i / 16) / 14), true);


    state = BASHING_RIGHT_STATE;
    _jobSprite->changeAnimation(BASHER_RIGHT);

}

void Basher::setWalkingRight(bool value) {
    walkingRight = value;
    if (walkingRight) {
        _jobSprite->changeAnimation(BASHER_RIGHT);
        state = BASHING_RIGHT_STATE;
    } else {
        _jobSprite->changeAnimation(BASHER_LEFT);
        state = BASHING_LEFT_STATE;
    }


}

void Basher::updateStateMachine(int deltaTime, Level *levelAttributes, IMaskManager *mask) {
    switch (state) {
        case BASHING_RIGHT_STATE:

            if (!bashRight(mask, deltaTime)) {
                isFinished = true;
                _nextJob = Jobs::WALKER;
            }

            break;


        case BASHING_LEFT_STATE:

            if (!bashLeft(mask, deltaTime)) {
                isFinished = true;
                _nextJob = Jobs::WALKER;
            }
    }
}

bool Basher::bashRight(IMaskManager *mask, int time) {
    glm::ivec2 posBase = _jobSprite->getPosition();
    posBase += glm::ivec2(8, 16);
    int y = posBase.y;
    int x = posBase.x;

    bool canBash = false;
    for (int i = 0; i <= 6; ++i) {
        for (int j = 0; j <= 8; ++j) {
            auto pixel = mask->getPixel(x + i, y - 1 - j);
            if (pixel == -1) {
                canBash = true;
            }
        }
    }
    for (int i = 0; i <= 6; ++i) {
        auto pixel = mask->getPixel(x + 7, y - 2 - i);

        if (pixel == -1) {
            canBash = true;
        }
    }

    if (!canBash) {
        return false;
    }

    int currentFrame = _jobSprite->getAnimationCurrentFrame();
    if (currentFrame == 2 || currentFrame == 18) {
        for (int i = 0; i <= 6; ++i) {
            for (int j = 0; j <= 8; ++j) {
                mask->eraseMask(x + i, y - 1 - j, time);
            }
        }

        for (int i = 0; i <= 6; ++i) {
            mask->eraseMask(x + 7, y - 2 - i, time);
        }
    }

    if (!((7 <= currentFrame && currentFrame <= 15) || (23 <= currentFrame && currentFrame <= 31))) {
        _jobSprite->incPosition(glm::vec2(1, 0));
    }


    return true;
}


bool Basher::bashLeft(IMaskManager *mask, int time) {
    glm::ivec2 posBase = _jobSprite->getPosition();
    posBase += glm::ivec2(7, 16);
    int y = posBase.y;
    int x = posBase.x;

    bool canBash = false;
    for (int i = 0; i <= 6; ++i) {
        for (int j = 0; j <= 8; ++j) {
            auto pixel = mask->getPixel(x - i, y - 1 - j);
            if (pixel == -1) {
                canBash = true;
            }
        }
    }
    for (int i = 0; i <= 6; ++i) {
        auto pixel = mask->getPixel(x - 7, y - 2 - i);

        if (pixel == -1) {
            canBash = true;
        }
    }

    if (!canBash) {
        return false;
    }

    int currentFrame = _jobSprite->getAnimationCurrentFrame();
    if (currentFrame == 2 || currentFrame == 18) {
        for (int i = 0; i <= 6; ++i) {
            for (int j = 0; j <= 8; ++j) {
                mask->eraseMask(x - i, y - 1 - j, time);
            }
        }

        for (int i = 0; i <= 6; ++i) {
            mask->eraseMask(x - 7, y - 2 - i, time);
        }
    }

    if (!((7 <= currentFrame && currentFrame <= 15) || (23 <= currentFrame && currentFrame <= 31))) {
        _jobSprite->incPosition(glm::vec2(-1, 0));
    }


    return true;
}







