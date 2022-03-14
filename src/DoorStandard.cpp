#include "DoorStandard.h"
#include "Game.h"
#include "ShaderManager.h"

DoorStandard::DoorStandard(ShaderManager *shaderManager) : Door(shaderManager) {
    _doorSprite = Sprite::createSprite(glm::vec2(41, 32), glm::vec2(1.f / 3, 1.f / 8),
                                       &_shaderManager->getShaderProgram(),
                                       &Game::spriteSheets().doorSprites);
    _escapeOffset = glm::vec2(13, 16);

    _doorSprite->setNumberAnimations(1);

    _doorSprite->setAnimationSpeed(0, 12);
    for (int i = 0; i < 6; i++) {
        _doorSprite->addKeyframe(0, glm::vec2(float(i % 3) / 3, float(i / 3) / 8));
    }

}

void DoorStandard::init() {
    _doorSprite->changeAnimation(0);
}


