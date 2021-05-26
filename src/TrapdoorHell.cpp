#include <iostream>
#include "ShaderManager.h"
#include "TrapdoorHell.h"
#include "Game.h"


TrapdoorHell::TrapdoorHell(ShaderManager *shaderManager) : Trapdoor(shaderManager) {
    _trapdoorSprite = Sprite::createSprite(glm::vec2(41, 25), glm::vec2(1.f / 2, 1.f / 10),
                                           &_shaderManager->getShaderProgram(),
                                           &Game::spriteSheets().trapdoorSprites);

    _enterOffset = glm::vec2(13, 0);

    _trapdoorSprite->setNumberAnimations(1);

    _trapdoorSprite->setAnimationSpeed(0, 12);
    for (int i = 0; i < 10; i++) {
        _trapdoorSprite->addKeyframe(0, glm::vec2(0.5, float(i) / 10));
    }
    _trapdoorSprite->changeAnimation(0);

}

void TrapdoorHell::init() {
    _trapdoorSprite->changeAnimation(0);
}
