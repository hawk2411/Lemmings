#include "PurplePercentageDisplay.h"
#include "PurpleNumFactory.h"

void PurplePercentageDisplay::init(ShaderManager *shaderManager) {
    _firstNum = PurpleNumFactory::createNum(shaderManager);
    _secondNum = PurpleNumFactory::createNum(shaderManager);
    _thirdNum = PurpleNumFactory::createNum(shaderManager);
    _percentage = PurpleNumFactory::createSymbol('%', shaderManager);
    setPosition(glm::vec2(0, 0));

}

void PurplePercentageDisplay::displayPercentage(int num) {
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

void PurplePercentageDisplay::render() {
    _firstNum->render();
    _secondNum->render();
    _thirdNum->render();
    _percentage->render();

}

void PurplePercentageDisplay::setPosition(glm::vec2 position) {
    this->_position = position;
    _firstNum->setPosition(this->_position + glm::vec2(0, 0));
    _secondNum->setPosition(this->_position + glm::vec2(7, 0));
    _thirdNum->setPosition(this->_position + glm::vec2(14, 0));
    _percentage->setPosition(this->_position + glm::vec2(21, 0));
}






