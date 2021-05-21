#include "Miner.h"
#include "Game.h"
#include "Scene.h"
#include "Utils.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum MinerAnims {
    MINER_RIGHT, MINER_LEFT
};

Miner::Miner() : Job(Jobs::MINER) {

}

void Miner::initAnims(ShaderProgram &shaderProgram) {
    _jobSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f / 16, 1.f / 14), &shaderProgram,
                                      &Game::spriteSheets().lemmingAnimations,
                                      &Game::spriteSheets().rotatedLemmingAnimations);
    _jobSprite->setNumberAnimations(2);


    // MINER
    _jobSprite->setAnimationSpeed(MINER_RIGHT, 12);
    for (int i = 0; i < 24; i++)
        if (i < 8) {
            _jobSprite->addKeyframe(MINER_RIGHT, glm::vec2(float(i + 8) / 16, 8.0f / 14));
        } else {
            _jobSprite->addKeyframe(MINER_RIGHT, glm::vec2(float(i - 8) / 16, 9.0f / 14));
        }

    _jobSprite->setAnimationSpeed(MINER_LEFT, 12);
    for (int i = 0; i < 24; i++)
        if (i < 8) {
            _jobSprite->addKeyframe(MINER_LEFT, glm::vec2((15 - float(i + 8)) / 16, 8.0f / 14), true);
        } else {
            _jobSprite->addKeyframe(MINER_LEFT, glm::vec2(((23 - float(i)) / 16), 9.0f / 14), true);
        }

    state = MINER_RIGHT_STATE;
    _jobSprite->changeAnimation(MINER_RIGHT);


}

void Miner::setWalkingRight(bool value) {
    walkingRight = value;

    if (walkingRight) {
        state = MINER_RIGHT_STATE;
        _jobSprite->changeAnimation(MINER_RIGHT);
    } else {
        state = MINER_LEFT_STATE;
        _jobSprite->changeAnimation(MINER_LEFT);
    }
}

void Miner::updateStateMachine(int deltaTime, Level *levelAttributes, IMaskManager *mask) {
    int fall;

    switch (state) {

        case MINER_RIGHT_STATE:

            if (!canMineRight(mask)) {
                isFinished = true;

                int fall = collisionFloor(3, levelAttributes->maskedMap);
                if (fall >= 3) {
                    _nextJob = Jobs::FALLER;
                } else {
                    _nextJob = Jobs::WALKER;
                }
            } else {
                mineRight(mask);
            }

            break;
        case MINER_LEFT_STATE:
            if (!canMineLeft(mask)) {
                isFinished = true;

                int fall = collisionFloor(3, levelAttributes->maskedMap);
                if (fall >= 3) {
                    _nextJob = Jobs::FALLER;
                } else {
                    _nextJob = Jobs::WALKER;
                }
            } else {
                mineLeft(mask);
            }
    }
}


//void Miner::printMine() {
//    glm::ivec2 posBase = _jobSprite->getPosition();
//
//    posBase += glm::ivec2(10, 16);
//
//    int x = posBase.x;
//    int y = posBase.y;
//
//    for (int i = 0; i < 3; ++i) {
//        Utils::changeTexelColor(Level::currentLevel().getLevelAttributes()->levelTexture.getId(), x + i, y, 120, 77, 0,
//                                255);
//        Scene::getInstance().applyMask(x + i, y);
//
//        Utils::changeTexelColor(Level::currentLevel().getLevelAttributes()->levelTexture.getId(), x + i, y - 12, 120,
//                                77, 0, 255);
//        Scene::getInstance().applyMask(x + i, y - 12);
//    }
//
//    for (int i = 0; i < 12; i += 11) {
//        Utils::changeTexelColor(Level::currentLevel().getLevelAttributes()->levelTexture.getId(), x + 3, y - i, 120, 77,
//                                0, 255);
//        Scene::getInstance().applyMask(x + 3, y - i);
//
//        Utils::changeTexelColor(Level::currentLevel().getLevelAttributes()->levelTexture.getId(), x + 3, y - (i + 1),
//                                120, 77, 0, 255);
//        Scene::getInstance().applyMask(x + 3, y - (i + 1));
//    }
//
//    for (int i = 1; i < 12; ++i) {
//        Utils::changeTexelColor(Level::currentLevel().getLevelAttributes()->levelTexture.getId(), x + 4, y - i, 120, 77,
//                                0, 255);
//        Scene::getInstance().applyMask(x + 4, y - i);
//    }
//
//    for (int i = 2; i < 11; ++i) {
//        Utils::changeTexelColor(Level::currentLevel().getLevelAttributes()->levelTexture.getId(), x + 5, y - i, 120, 77,
//                                0, 255);
//        Scene::getInstance().applyMask(x + 5, y - i);
//    }
//
//}

void Miner::mineRight(IMaskManager *mask) {
    //printMine();
    glm::ivec2 posBase = _jobSprite->getPosition();

    posBase += glm::ivec2(10, 16);

    if (_jobSprite->getAnimationCurrentFrame() == 2) {
        int x = posBase.x;
        int y = posBase.y;

        for (int i = 0; i < 4; ++i) {
            mask->eraseMask(x + i, y, 0);
            mask->eraseMask(x + i, y - (i + 1), 0);
            mask->eraseMask(x + i, y - (i + 2), 0);
            mask->eraseMask(x + i, y - 12, 0);
            mask->eraseMask(x + i, y - 11, 0);
            mask->eraseMask(x + i, y - 10, 0);
        }

        for (int i = 0; i < 12; ++i) {
            mask->eraseMask(x + 4, y - i, 0);
        }

        for (int i = 2; i < 11; ++i) {
            mask->eraseMask(x + 5, y - i, 0);
        }
    }
    if (_jobSprite->getAnimationCurrentFrame() == 17) {
        _jobSprite->incPosition(glm::vec2(2, 1));

    }

}

bool Miner::canMineRight(IMaskManager *mask) {
    glm::ivec2 posBase = _jobSprite->getPosition();

    posBase += glm::ivec2(10, 17);

    int x = posBase.x;
    int y = posBase.y;

    for (int i = 0; i < 3; ++i) {
        if (mask->getPixel(x + i, y) == -1) {
            return true;
        }
        if (mask->getPixel(x + i, y - (i + 1)) == -1) {
            return true;
        }
        if (mask->getPixel(x + i, y - (i + 2)) == -1) {
            return true;
        }
        if (mask->getPixel(x + i, y - 12) == -1) {
            return true;
        }
        if (mask->getPixel(x + i, y - 11) == -1) {
            return true;
        }
        if (mask->getPixel(x + i, y - 10) == -1) {
            return true;
        }

    }

    for (int i = 0; i < 12; i += 11) {
        if (mask->getPixel(x + 3, y - i) == -1) {
            return true;
        }
        if (mask->getPixel(x + 3, y - (i + 1)) == -1) {
            return true;
        }
    }

    for (int i = 1; i < 12; ++i) {
        if (mask->getPixel(x + 4, y - i) == -1) {
            return true;
        }
    }

    for (int i = 2; i < 11; ++i) {
        if (mask->getPixel(x + 5, y - i) == -1) {
            return true;
        }
    }

    return false;
}


bool Miner::canMineLeft(IMaskManager *mask) {
    glm::ivec2 posBase = _jobSprite->getPosition();

    posBase += glm::ivec2(0, 17);

    int x = posBase.x;
    int y = posBase.y;

    for (int i = 1; i < 11; ++i) {
        if (mask->getPixel(x, y - i) == -1) {
            return true;
        }
    }

    for (int i = 0; i < 12; ++i) {
        if (mask->getPixel(x + 1, y - i) == -1) {
            return true;
        }
    }

    for (int i = 0; i < 12; i += 11) {
        if (mask->getPixel(x + 2, y - i) == -1) {
            return true;
        }
        if (mask->getPixel(x + 2, y - (i + 1)) == -1) {
            return true;
        }
    }

    for (int i = 2; i < 6; ++i) {
        for (int j = 0; j < 13; j += 12) {
            if (mask->getPixel(x + i, y - j) == -1) {
                return true;
            }

            if (mask->getPixel(x + i, y - (j + 1)) == -1) {
                return true;
            }
        }
    }
    return false;
}

void Miner::mineLeft(IMaskManager *mask) {
    glm::ivec2 posBase = _jobSprite->getPosition();
    posBase += glm::ivec2(0, 16);

    if (_jobSprite->getAnimationCurrentFrame() == 2) {
        int x = posBase.x;
        int y = posBase.y;

        for (int i = 1; i < 11; ++i) {
            mask->eraseMask(x, y - i, 0);
        }

        for (int i = 0; i < 12; ++i) {
            mask->eraseMask(x + 1, y - i, 0);
        }

        for (int i = 0; i < 12; i += 11) {
            mask->eraseMask(x + 2, y - i, 0);
            mask->eraseMask(x + 2, y - (i + 1), 0);
        }

        for (int i = 2; i < 6; ++i) {
            for (int j = 0; j < 13; j += 12) {
                mask->eraseMask(x + i, y - j, 0);
                mask->eraseMask(x + i, y - (j + 1), 0);
            }
        }
    }

    if (_jobSprite->getAnimationCurrentFrame() == 17) {
        _jobSprite->incPosition(glm::vec2(-2, 1));

    }
}





