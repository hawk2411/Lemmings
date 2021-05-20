#include "Game.h"
#include "PurpleNumFactory.h"
#include "ShaderManager.h"

std::unique_ptr<Sprite> PurpleNumFactory::createNum() {
    auto numSprite = Sprite::createSprite(glm::ivec2(6, 9), glm::vec2(18. / 128, 24. / 64),
                                          &ShaderManager::getInstance().getShaderProgram(),
                                          &Game::spriteSheets().purpleNumSprites);
    numSprite->setNumberAnimations(11);
    for (int i = 0; i < 11; ++i) {
        numSprite->addKeyframe(i, this->numPositions[i]);
    }
    numSprite->changeAnimation(10);

    return numSprite;
}

std::unique_ptr<Sprite> PurpleNumFactory::createSymbol(char symbol) {
    auto numSprite = Sprite::createSprite(glm::ivec2(6, 9), glm::vec2(18. / 128, 24. / 64),
                                          &ShaderManager::getInstance().getShaderProgram(),
                                          &Game::spriteSheets().purpleNumSprites);
    numSprite->setNumberAnimations(1);

    if (symbol == '%') {
        numSprite->addKeyframe(0, glm::vec2(72. / 128, 24. / 64));
        numSprite->changeAnimation(0);
    } else {
        numSprite.reset();
    }

    return numSprite;
}
