#include "ButtonNumFactory.h"
#include "ShaderManager.h"
#include "Game.h"

std::unique_ptr<Sprite> ButtonNumFactory::createNum(ShaderManager* shaderManager) {

    glm::vec2 _numPositions[11] = {
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
            glm::vec2(0.5, 0.5)
    };

    auto numSprite = Sprite::createSprite(glm::ivec2(3, 8), glm::vec2(3.f / 16, 0.25),
                                          &shaderManager->getShaderProgram(),
                                          &Game::spriteSheets().numSprites);
    numSprite->setNumberAnimations(11);
    for (int i = 0; i < 11; ++i) {
        numSprite->addKeyframe(i, _numPositions[i]);
    }
    numSprite->changeAnimation(10);

    return numSprite;
}

