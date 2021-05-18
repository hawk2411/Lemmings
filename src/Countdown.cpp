#include "ButtonNumFactory.h"
#include "Level.h"
#include "Countdown.h"

const int MAX_SEC = 5;

Countdown::Countdown() {
    _over = false;
    _countNum = ButtonNumFactory::instance().createNum();
    _countNum->changeAnimation(MAX_SEC);
    _goalTime = 0;
    _isStarted = false;
}

void Countdown::render() {

    if(!_isStarted) {
        return;
    }

    glm::vec2 oldPosition = _countNum->getPosition();
    _countNum->setPosition(oldPosition - Level::currentLevel().getLevelAttributes()->cameraPos);
    _countNum->render();
    _countNum->setPosition(oldPosition);

}

void Countdown::setPosition(glm::vec2 position) {
    _countNum->setPosition(position);
}

void Countdown::update(int deltaTime) {
    if(!_isStarted) {
        return;
    }
    int currentSec = _goalTime - deltaTime;
    if (currentSec <= 0) {
        _over = true;
    } else {
        _countNum->changeAnimation(currentSec);
    }
}


void Countdown::start(int goalTime) {
    _goalTime = MAX_SEC + goalTime;
    _isStarted = true;
}

void Countdown::reset(){
    _goalTime = 0;
    _isStarted = false;
}

bool Countdown::isStarted() const {
    return _isStarted;
}