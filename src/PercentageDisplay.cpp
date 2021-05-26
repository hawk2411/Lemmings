#include "ShaderManager.h"
#include "PercentageDisplay.h"
#include "GreenNumFactory.h"

void PercentageDisplay::init(ShaderManager *shaderManager) {
    firstNum = GreenNumFactory::createNum(shaderManager);
    secondNum = GreenNumFactory::createNum(shaderManager);
    thirdNum = GreenNumFactory::createNum(shaderManager);
    percentage = GreenNumFactory::createSymbol('%', shaderManager);
    setPosition(glm::vec2(0, 0));

}

void PercentageDisplay::displayPercentage(int num) {
    int firstDigit = num / 100;
    int secondDigit = (num / 10) % 10;
    int thirdDigit = num % 10;

    if (firstDigit == 0) {
        firstNum->changeAnimation(10);

        if (secondDigit == 0) {
            secondNum->changeAnimation(10);
        } else {
            secondNum->changeAnimation(secondDigit);
        }
    } else {
        firstNum->changeAnimation(firstDigit);
        secondNum->changeAnimation(secondDigit);
    }

    thirdNum->changeAnimation(thirdDigit);

}

void PercentageDisplay::render() {
    firstNum->render();
    secondNum->render();
    thirdNum->render();
    percentage->render();

}

void PercentageDisplay::setPosition(glm::vec2 newPosition) {
    position = newPosition;
    firstNum->setPosition(this->position + glm::vec2(4, 0));
    secondNum->setPosition(this->position + glm::vec2(12, 0));
    thirdNum->setPosition(this->position + glm::vec2(20, 0));
    percentage->setPosition(this->position + glm::vec2(28, 0));
}



