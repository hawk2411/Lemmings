#include "TimeDisplay.h"
#include "GreenNumFactory.h"

void TimeDisplay::init(ShaderManager *shaderManager) {
    _minutes = GreenNumFactory::createNum(shaderManager);
    _hyphen = GreenNumFactory::createSymbol('-', shaderManager);
    _firstDigitSeconds = GreenNumFactory::createNum(shaderManager);
    _secondDigitSeconds = GreenNumFactory::createNum(shaderManager);
    setPosition(glm::vec2(0, 0));

}

void TimeDisplay::displayTime(int num) {
    int firstDigit = num / 60;
    int secondDigit = (num % 60) / 10;
    int thirdDigit = (num % 60) % 10;

    _minutes->changeAnimation(firstDigit);
    _firstDigitSeconds->changeAnimation(secondDigit);
    _secondDigitSeconds->changeAnimation(thirdDigit);
}

void TimeDisplay::render() {
    _minutes->render();
    _firstDigitSeconds->render();
    _secondDigitSeconds->render();
    _hyphen->render();
}

void TimeDisplay::setPosition(glm::vec2 position) {
    this->_position = position;
    _minutes->setPosition(this->_position + glm::vec2(4, 0));
    _hyphen->setPosition(this->_position + glm::vec2(12, 0));
    _firstDigitSeconds->setPosition(this->_position + glm::vec2(20, 0));
    _secondDigitSeconds->setPosition(this->_position + glm::vec2(28, 0));

}



