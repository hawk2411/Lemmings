#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Blocker.h"
#include "Game.h"
#include "Scene.h"
#include "JobFactory.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


void Blocker::initAnims(ShaderProgram &shaderProgram) {
    jobSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f / 16, 1.f / 14), &shaderProgram,
                                     &Game::spriteSheets().lemmingAnimations,
                                     &Game::spriteSheets().rotatedLemmingAnimations);
    jobSprite->setNumberAnimations(1);

    // BLOCKER
    jobSprite->setAnimationSpeed( 0, 12);
    for (int i = 0; i < 16; i++)
        jobSprite->addKeyframe(0, glm::vec2(float(i) / 16, 3.0f / 14));

    state = BLOCKING_STATE;
    jobSprite->changeAnimation(0);

}

void Blocker::setWalkingRight(bool value) {
    walkingRight = value;
}

void Blocker::updateStateMachine(int deltaTime) {

    switch (state) {
        case BLOCKING_STATE:

            glm::ivec2 posBase = jobSprite->getPosition();

            posBase += glm::ivec2(3, 1);

            int x = posBase.x;
            int y = posBase.y;

            for (int i = 0; i < 10; i += 9) {
                for (int j = 0; j < 16; ++j) {
                    Scene::getInstance().applySpecialMask(x + i, y + j);
                }
            }

            break;
    }
}