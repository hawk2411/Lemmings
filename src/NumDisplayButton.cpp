#include "NumDisplayButton.h"
#include "ButtonNumFactory.h"

void NumDisplayButton::initAux(ShaderManager *shaderManager) {
    _leftNum = ButtonNumFactory::createNum(shaderManager);
    _rightNum = ButtonNumFactory::createNum(shaderManager);
}

void NumDisplayButton::displayNumAux(int firstDigit, int secondDigit) {
    _leftNum->changeAnimation(firstDigit);
    _rightNum->changeAnimation(secondDigit);
}

void NumDisplayButton::setPosition(glm::vec2 position) {
    this->_position = position;
    _leftNum->setPosition(this->_position + glm::vec2(4, 1));
    _rightNum->setPosition(this->_position + glm::vec2(8, 1));
}

