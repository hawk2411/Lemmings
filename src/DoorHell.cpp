#include "DoorHell.h"
#include "Game.h"
#include "ShaderManager.h"

DoorHell::DoorHell(ShaderManager *shaderManager) : Door(shaderManager) {

    _doorSprite = Sprite::createSprite(glm::vec2(41, 32), glm::vec2(1.f / 3, 1.f / 8),
                                       &_shaderManager->getShaderProgram(),
                                       &Game::spriteSheets().doorSprites);

    _escapeOffset = glm::vec2(13, 16);

    _doorSprite->setNumberAnimations(1);

    _doorSprite->setAnimationSpeed(0, default_animation_speed);
    for (int i = 2; i < 8; i++) {
        _doorSprite->addKeyframe(0, glm::vec2(2.f / 3, float(i) / 8));
    }

    _doorSprite->changeAnimation(0);
}

void DoorHell::init() {
    _doorSprite->changeAnimation(0);
}
