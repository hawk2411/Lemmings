#include "Game.h"
#include "PurpleNumFactory.h"
#include "ShaderManager.h"

unique_ptr<Sprite> PurpleNumFactory::createNum(ShaderManager *shaderManager) {

    glm::vec2 numPositions[11] = {
            glm::vec2(0, 0),
            glm::vec2(18. / 128, 0),
            glm::vec2(36. / 128, 0),
            glm::vec2(54. / 128, 0),
            glm::vec2(72. / 128, 0),
            glm::vec2(90. / 128, 0),
            glm::vec2(0, 24. / 64),
            glm::vec2(18. / 128, 24. / 64),
            glm::vec2(36. / 128, 24. / 64),
            glm::vec2(54. / 128, 24. / 64),
            glm::vec2(90. / 128, 24. / 64)
    };

    auto numSprite = Sprite::createSprite(glm::ivec2(6, 9), glm::vec2(18. / 128, 24. / 64),
                                          &shaderManager->getShaderProgram(),
                                          &Game::spriteSheets().purpleNumSprites);
    numSprite->setNumberAnimations(11);
    for (int i = 0; i < 11; ++i) {
        numSprite->addKeyframe(i, numPositions[i]);
    }
    numSprite->changeAnimation(10);

    return numSprite;
}

unique_ptr<Sprite> PurpleNumFactory::createSymbol(char symbol, ShaderManager *shaderManager) {
    auto numSprite = Sprite::createSprite(glm::ivec2(6, 9), glm::vec2(18. / 128, 24. / 64),
                                          &shaderManager->getShaderProgram(),
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
