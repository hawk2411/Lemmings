#include "NumDisplay.h"


void NumDisplay::init() {
    initAux();

    setPosition(glm::vec2(0, 0));
}

void NumDisplay::displayNum(int num) {
    int firstDigit = num / 10;
    int secondDigit = num % 10;

    displayNumAux(firstDigit, secondDigit);
}

void NumDisplay::render() {
    if (leftNum) {
        leftNum->render();
    }

    if (rightNum) {
        rightNum->render();
    }
}
