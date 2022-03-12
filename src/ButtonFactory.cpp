#include <iostream>
#include "Game.h"
#include "Scene.h"
#include "ButtonFactory.h"
#include "Sprite.h"
#include "ShaderManager.h"


Button ButtonFactory::createButton(int buttonName, ShaderManager *shaderManager) {
    Button button;
    button.init(shaderManager);

    auto buttonSprite = Sprite::createSprite(glm::ivec2(15, 23), glm::vec2(15. / 128, 23. / 64),
                                             &shaderManager->getShaderProgram(),
                                             &Game::spriteSheets().buttonSprites);
    buttonSprite->setNumberAnimations(1);

    glm::vec2 textureCoord;

    switch (buttonName) {
        case Button::MINUS_BUTTON:
            textureCoord = glm::vec2(0, 0);
            break;
        case Button::PLUS_BUTTON:
            textureCoord = glm::vec2(0.125, 0);
            break;
        case Button::CLIMBER_BUTTON:
            textureCoord = glm::vec2(0.25, 0.5);
            break;
        case Button::FLOATER_BUTTON:
            textureCoord = glm::vec2(0.5, 0.5);
            break;
        case Button::EXPLODER_BUTTON:
            textureCoord = glm::vec2(0.5, 0);
            break;
        case Button::BLOCKER_BUTTON:
            textureCoord = glm::vec2(80. / 128, 0);
            break;
        case Button::BUILDER_BUTTON:
            textureCoord = glm::vec2(0.125, 0.5);
            break;
        case Button::BASHER_BUTTON:
            textureCoord = glm::vec2(0, 0.5);
            break;
        case Button::MINER_BUTTON:
            textureCoord = glm::vec2(80. / 128, 0.5);
            break;
        case Button::DIGGER_BUTTON:
            textureCoord = glm::vec2(0.375, 0.5);
            break;
        case Button::PAUSE_BUTTON:
            textureCoord = glm::vec2(0.25, 0);
            break;
        case Button::NUKE_BUTTON:
            textureCoord = glm::vec2(0.375, 0);
            break;
        case Button::SPEED_BUTTON:
            textureCoord = glm::vec2(96. / 128, 0);
            break;
        default:
            throw std::runtime_error("unknown button id");
            break;
    }

    buttonSprite->addKeyframe(0, textureCoord);
    buttonSprite->changeAnimation(0);

    button.setSprite(std::move(buttonSprite));

    return button;
}

