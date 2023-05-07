#include <iostream>
#include "ShaderManager.h"
#include "TrapdoorStandard.h"
#include "Game.h"


TrapdoorStandard::TrapdoorStandard(ShaderManager *shaderManager) : Trapdoor(shaderManager) {
    _trapdoorSprite = Sprite::createSprite(glm::vec2(41, 25), glm::vec2(1.f / 2, 1.f / 10),
                                           &_shaderManager->getShaderProgram(),
                                           &Game::spriteSheets().trapdoorSprites);
    _enterOffset = glm::vec2(13, 0);

    _trapdoorSprite->setNumberAnimations(1);

    _trapdoorSprite->setAnimationSpeed(0, default_animation_speed);
    for (int i = 0; i < 10; i++) {
        _trapdoorSprite->addKeyframe(0, glm::vec2(0, float(i) / 10));
    }

    _trapdoorSprite->changeAnimation(0);

}

void TrapdoorStandard::init() {

    _trapdoorSprite->changeAnimation(0);
}
