#include <iostream>
#include "DoorEgypt.h"
#include "Game.h"
#include "ShaderManager.h"

DoorEgypt::DoorEgypt(ShaderManager *shaderManager) : Door(shaderManager) {
    _doorSprite = Sprite::createSprite(glm::vec2(41, 32), glm::vec2(1.f / 3, 1.f / 8),
                                       &_shaderManager->getShaderProgram(),
                                       &Game::spriteSheets().doorSprites);

    _escapeOffset = glm::vec2(13, 16);

    _doorSprite->setNumberAnimations(1);

    _doorSprite->setAnimationSpeed(0, 12);
    for (int i = 2; i < 8; i++) {
        _doorSprite->addKeyframe(0, glm::vec2(0, float(i) / 8));
    }
    _doorSprite->changeAnimation(0);

}

void DoorEgypt::init() {
    _doorSprite->changeAnimation(0);
}
