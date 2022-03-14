#include "ButtonNumFactory.h"
#include "Countdown.h"

Countdown::Countdown(ShaderManager *shaderManager) : _shaderManager(shaderManager) {
    _over = false;
    _countNum = ButtonNumFactory::createNum(_shaderManager);
    _countNum->changeAnimation(MAX_SEC);
    _goalTime = 0;
    _isStarted = false;
}

void Countdown::render(const glm::vec2 &cameraPos) {

    if(!_isStarted) {
        return;
    }

    glm::vec2 oldPosition = _countNum->getPosition();
    _countNum->setPosition(oldPosition - cameraPos);
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
    _currentTime += static_cast<float>(deltaTime);
    //TODO check if this is really correct.
    if( _currentTime > 300.f) {
        _currentTime=0.0f;
        _goalTime--;
    }
    if (_goalTime <= 0) {
        _over = true;
    } else {
        _countNum->changeAnimation(_goalTime);
    }
}


void Countdown::start(int goalTime) {
    _goalTime = MAX_SEC + goalTime;
    _isStarted = true;
}

bool Countdown::isOver() const {
    return _over;
}


void Countdown::reset(){
    _goalTime = 0;
    _isStarted = false;
}

bool Countdown::isStarted() const {
    return _isStarted;
}