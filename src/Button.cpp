#include "Button.h"
#include "ShaderManager.h"


void Button::init(ShaderManager *shaderManager) {
    _numDisplay.init(shaderManager);

    setPosition(glm::vec2(0, 0));
}

void Button::render() {
    _numDisplay.render();
    _buttonSprite->render();
}

void Button::setSprite(std::unique_ptr<Sprite> sprite) {

    _buttonSprite = std::move(sprite);
    _buttonSprite->setPosition(_position);
}

glm::vec2 Button::getPosition() {
    return _position;
}

void Button::setPosition(glm::vec2 position) {
    this->_position = position;

    _numDisplay.setPosition(position);

    if (_buttonSprite != nullptr) {
        _buttonSprite->setPosition(position);
    }
}

void Button::setNum(int num) {
    _numDisplay.displayNum(num);
}