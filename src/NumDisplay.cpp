#include "NumDisplay.h"
#include "ShaderManager.h"


void NumDisplay::init(ShaderManager *shaderManager) {
    initAux(shaderManager);

    setPosition(glm::vec2(0, 0));
}

void NumDisplay::displayNum(int num) {
    int firstDigit = num / 10;
    int secondDigit = num % 10;

    displayNumAux(firstDigit, secondDigit);
}

void NumDisplay::render() {
    if (_leftNum) {
        _leftNum->render();
    }

    if (_rightNum) {
        _rightNum->render();
    }
}
