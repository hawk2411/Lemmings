#include "Button.h"
#include "ShaderManager.h"


void Button::init(ShaderManager *shaderManager) {
    numDisplay.init(shaderManager);

    setPosition(glm::vec2(0, 0));
}

void Button::render() {
    numDisplay.render();
    buttonSprite->render();
}

void Button::setSprite(std::unique_ptr<Sprite> sprite) {

    buttonSprite = std::move(sprite);
    buttonSprite->setPosition(position);
}

glm::vec2 Button::getPosition() {
    return position;
}

void Button::setPosition(glm::vec2 position) {
    this->position = position;

    numDisplay.setPosition(position);

    if (buttonSprite != nullptr) {
        buttonSprite->setPosition(position);
    }
}

void Button::setNum(int num) {
    numDisplay.displayNum(num);
}