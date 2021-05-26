#include "NumDisplayGreen.h"
#include "GreenNumFactory.h"

void NumDisplayGreen::initAux(ShaderManager *shaderManager) {
    leftNum = GreenNumFactory::createNum(shaderManager);
    rightNum = GreenNumFactory::createNum(shaderManager);

}

void NumDisplayGreen::displayNumAux(int firstDigit, int secondDigit) {
    if (firstDigit != 0) {
        leftNum->changeAnimation(firstDigit);
    } else {
        leftNum->changeAnimation(10);
    }

    rightNum->changeAnimation(secondDigit);

}

void NumDisplayGreen::setPosition(glm::vec2 position) {
    this->position = position;

    leftNum->setPosition(this->position + glm::vec2(4, 0));
    rightNum->setPosition(this->position + glm::vec2(12, 0));

}

