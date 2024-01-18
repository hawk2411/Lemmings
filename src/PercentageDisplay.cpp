#include "ShaderManager.h"
#include "PercentageDisplay.h"
#include "GreenNumFactory.h"

void PercentageDisplay::init(ShaderManager *shaderManager) {
    _firstNum = GreenNumFactory::createNum(shaderManager);
    _secondNum = GreenNumFactory::createNum(shaderManager);
    _thirdNum = GreenNumFactory::createNum(shaderManager);
    _percentage = GreenNumFactory::createSymbol('%', shaderManager);
    setPosition(glm::vec2(0, 0));

}

void PercentageDisplay::displayPercentage(int num) {
    int firstDigit = num / 100;
    int secondDigit = (num / 10) % 10;
    int thirdDigit = num % 10;

    if (firstDigit == 0) {
        _firstNum->changeAnimation(10);

        if (secondDigit == 0) {
            _secondNum->changeAnimation(10);
        } else {
            _secondNum->changeAnimation(secondDigit);
        }
    } else {
        _firstNum->changeAnimation(firstDigit);
        _secondNum->changeAnimation(secondDigit);
    }

    _thirdNum->changeAnimation(thirdDigit);

}

void PercentageDisplay::render() {
    _firstNum->render();
    _secondNum->render();
    _thirdNum->render();
    _percentage->render();

}

void PercentageDisplay::setPosition(glm::vec2 newPosition) {
    _position = newPosition;
    _firstNum->setPosition(this->_position + glm::vec2(4, 0));
    _secondNum->setPosition(this->_position + glm::vec2(12, 0));
    _thirdNum->setPosition(this->_position + glm::vec2(20, 0));
    _percentage->setPosition(this->_position + glm::vec2(28, 0));
}



