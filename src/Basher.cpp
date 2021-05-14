#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Basher.h"
#include "Game.h"
#include "Scene.h"
#include "JobFactory.h"
#include "Utils.h"

#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum BasherAnims {
    BASHER_RIGHT, BASHER_LEFT
};

void Basher::initAnims(ShaderProgram &shaderProgram) {
    jobSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f / 16, 1.f / 14), &shaderProgram,
                                     &Game::spriteSheets().lemmingAnimations,
                                     &Game::spriteSheets().rotatedLemmingAnimations);
    jobSprite->setNumberAnimations(2);

    // BASHER
    jobSprite->setAnimationSpeed(BASHER_RIGHT, 12);
    for (int i = 0; i < 32; i++)
        jobSprite->addKeyframe(BASHER_RIGHT, glm::vec2(float(i % 16) / 16, (6.0f + i / 16) / 14));
    jobSprite->setAnimationSpeed(BASHER_LEFT, 12);
    for (int i = 0; i < 32; i++)
        jobSprite->addKeyframe(BASHER_LEFT, glm::vec2((15 - float(i % 16)) / 16, (6.0f + i / 16) / 14), true);


    state = BASHING_RIGHT_STATE;
    jobSprite->changeAnimation(BASHER_RIGHT);

}

void Basher::setWalkingRight(bool value) {
    walkingRight = value;
    if (walkingRight) {
        jobSprite->changeAnimation(BASHER_RIGHT);
        state = BASHING_RIGHT_STATE;
    } else {
        jobSprite->changeAnimation(BASHER_LEFT);
        state = BASHING_LEFT_STATE;
    }


}

void Basher::updateStateMachine(int deltaTime) {
    switch (state) {
        case BASHING_RIGHT_STATE:

            if (!bashRight()) {
                isFinished = true;
                nextJob = JobFactory::instance().createWalkerJob();
            }

            break;


        case BASHING_LEFT_STATE:

            if (!bashLeft()) {
                isFinished = true;
                nextJob = JobFactory::instance().createWalkerJob();
            }
    }
}

bool Basher::bashRight() {
    glm::ivec2 posBase = jobSprite->getPosition();
    posBase += glm::ivec2(8, 16);
    int y = posBase.y;
    int x = posBase.x;

    bool canBash = false;
    for (int i = 0; i <= 6; ++i) {
        for (int j = 0; j <= 8; ++j) {
            int pixel = Scene::getInstance().getPixel(x + i, y - 1 - j);
            if (pixel == -1) {
                canBash = true;
            }
        }
    }
    for (int i = 0; i <= 6; ++i) {
        int pixel = Scene::getInstance().getPixel(x + 7, y - 2 - i);

        if (pixel == -1) {
            canBash = true;
        }
    }

    if (!canBash) {
        return false;
    }

    int currentFrame = jobSprite->getAnimationCurrentFrame();
    if (currentFrame == 2 || currentFrame == 18) {
        for (int i = 0; i <= 6; ++i) {
            for (int j = 0; j <= 8; ++j) {
                Scene::getInstance().eraseMask(x + i, y - 1 - j);
            }
        }

        for (int i = 0; i <= 6; ++i) {
            Scene::getInstance().eraseMask(x + 7, y - 2 - i);
        }
    }

    if (!((7 <= currentFrame && currentFrame <= 15) || (23 <= currentFrame && currentFrame <= 31))) {
        jobSprite->incPosition(glm::vec2(1, 0));
    }


    return true;
}


bool Basher::bashLeft() {
    glm::ivec2 posBase = jobSprite->getPosition();
    posBase += glm::ivec2(7, 16);
    int y = posBase.y;
    int x = posBase.x;

    bool canBash = false;
    for (int i = 0; i <= 6; ++i) {
        for (int j = 0; j <= 8; ++j) {
            int pixel = Scene::getInstance().getPixel(x - i, y - 1 - j);
            if (pixel == -1) {
                canBash = true;
            }
        }
    }
    for (int i = 0; i <= 6; ++i) {
        int pixel = Scene::getInstance().getPixel(x - 7, y - 2 - i);

        if (pixel == -1) {
            canBash = true;
        }
    }

    if (!canBash) {
        return false;
    }

    int currentFrame = jobSprite->getAnimationCurrentFrame();
    if (currentFrame == 2 || currentFrame == 18) {
        for (int i = 0; i <= 6; ++i) {
            for (int j = 0; j <= 8; ++j) {
                Scene::getInstance().eraseMask(x - i, y - 1 - j);
            }
        }

        for (int i = 0; i <= 6; ++i) {
            Scene::getInstance().eraseMask(x - 7, y - 2 - i);
        }
    }

    if (!((7 <= currentFrame && currentFrame <= 15) || (23 <= currentFrame && currentFrame <= 31))) {
        jobSprite->incPosition(glm::vec2(-1, 0));
    }


    return true;
}






