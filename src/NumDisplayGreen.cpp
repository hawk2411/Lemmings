#include "NumDisplayGreen.h"
#include "GreenNumFactory.h"

void NumDisplayGreen::initAux(ShaderManager *shaderManager) {
    _leftNum = GreenNumFactory::createNum(shaderManager);
    _rightNum = GreenNumFactory::createNum(shaderManager);

}

void NumDisplayGreen::displayNumAux(int firstDigit, int secondDigit) {
    if (firstDigit != 0) {
        _leftNum->changeAnimation(firstDigit);
    } else {
        _leftNum->changeAnimation(10);
    }

    _rightNum->changeAnimation(secondDigit);

}

void NumDisplayGreen::setPosition(glm::vec2 position) {
    this->_position = position;

    _leftNum->setPosition(this->_position + glm::vec2(4, 0));
    _rightNum->setPosition(this->_position + glm::vec2(12, 0));

}

