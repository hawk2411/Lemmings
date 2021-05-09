#include "Game.h"
#include "GreenNumFactory.h"
#include "ShaderManager.h"

std::unique_ptr<Sprite> GreenNumFactory::createNum() {
    auto numSprite = Sprite::createSprite(glm::ivec2(7, 10), glm::vec2(38. / 256, 81. / 512),
                                          &ShaderManager::getInstance().getShaderProgram(),
                                          &Game::spriteSheets().greenNumSprites);
    numSprite->setNumberAnimations(11);
    for (int i = 0; i < 11; ++i) {
        numSprite->addKeyframe(i, this->numPositions[i]);
    }
    numSprite->changeAnimation(10);

    return numSprite;
}

std::unique_ptr<Sprite> GreenNumFactory::createSymbol(char symbol) {
    auto numSprite = Sprite::createSprite(glm::ivec2(7, 10), glm::vec2(38. / 256, 81. / 512),
                                          &ShaderManager::getInstance().getShaderProgram(),
                                          &Game::spriteSheets().greenNumSprites);
    numSprite->setNumberAnimations(1);

    if (symbol == '-') {
        numSprite->addKeyframe(0, glm::vec2(0.5, 0.5));
        numSprite->changeAnimation(0);
    } else if (symbol == '%') {
        numSprite->addKeyframe(0, glm::vec2(0.75, 0.5));
        numSprite->changeAnimation(0);
    } else {
        numSprite.reset();
    }


    return numSprite;
}
