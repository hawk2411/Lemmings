#include "NumDisplayButton.h"
#include "ButtonNumFactory.h"

void NumDisplayButton::initAux(ShaderManager *shaderManager) {
    leftNum = ButtonNumFactory::createNum(shaderManager);
    rightNum = ButtonNumFactory::createNum(shaderManager);
}

void NumDisplayButton::displayNumAux(int firstDigit, int secondDigit) {
    leftNum->changeAnimation(firstDigit);
    rightNum->changeAnimation(secondDigit);
}

void NumDisplayButton::setPosition(glm::vec2 position) {
    this->position = position;
    leftNum->setPosition(this->position + glm::vec2(4, 1));
    rightNum->setPosition(this->position + glm::vec2(8, 1));
}

