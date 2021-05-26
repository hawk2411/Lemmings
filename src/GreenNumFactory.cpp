#include "Game.h"
#include "GreenNumFactory.h"


unique_ptr<Sprite> GreenNumFactory::createNum(ShaderManager *shaderManager) {
    glm::vec2 numPositions[11] = {
            glm::vec2(0, 0),
            glm::vec2(0.25, 0),
            glm::vec2(0.5, 0),
            glm::vec2(0.75, 0),
            glm::vec2(0, 0.25),
            glm::vec2(0.25, 0.25),
            glm::vec2(0.5, 0.25),
            glm::vec2(0.75, 0.25),
            glm::vec2(0, 0.5),
            glm::vec2(0.25, 0.5),
            glm::vec2(0.75, 0.75)
    };

    auto numSprite = Sprite::createSprite(glm::ivec2(7, 10), glm::vec2(38. / 256, 81. / 512),
                                          &shaderManager->getShaderProgram(),
                                          &Game::spriteSheets().greenNumSprites);
    numSprite->setNumberAnimations(11);
    for (int i = 0; i < 11; ++i) {
        numSprite->addKeyframe(i, numPositions[i]);
    }
    numSprite->changeAnimation(10);

    return numSprite;
}

unique_ptr<Sprite> GreenNumFactory::createSymbol(char symbol, ShaderManager *shaderManager) {
    auto numSprite = Sprite::createSprite(glm::ivec2(7, 10), glm::vec2(38. / 256, 81. / 512),
                                          &shaderManager->getShaderProgram(),
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
