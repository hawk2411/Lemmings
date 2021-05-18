#include <iostream>
#include "Lemming.h"
#include "Game.h"
#include "ShaderManager.h"
#include "JobFactory.h"
#include "Utils.h"

#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


Lemming::Lemming(const glm::vec2 &initialPosition) {
    this->shaderProgram = &ShaderManager::getInstance().getShaderProgram();
    _job = JobFactory::createFallerJob();
    _job->initAnims(*shaderProgram);
    _position = initialPosition;
    _job->sprite()->setPosition(initialPosition);
    _alive = true;
    _isSaved = false;
}

void Lemming::update(int deltaTime) {
    if (_job->sprite()->update(deltaTime) == 0) {
        return;
    }

    if (outOfMap()) {
        _alive = false;
        delete _job;
        //lemming no longer has a job
        return;
    }
    if (_countdown.isStarted() && _countdown.isOver()) {
        changeJob(Jobs::EXPLODER);
        return;
    }
    //still not nuked
    _job->updateStateMachine(deltaTime);

    if (_countdown.isStarted()) {
        //countdown for nuke is running
        _countdown.setPosition(glm::vec2(6, -8) + _job->sprite()->getPosition());
        _countdown.update(deltaTime);
    }

    if (_job->finished()) {
        if (_job->getNextJob() == Jobs::UNKNOWN) {
            if (_job->getCurrentJob() == Jobs::ESCAPER) {
                _isSaved = true;
            } else {
                cout << "is finished but not alive" << endl;
                _alive = false;
            }
        }
        if (_alive && !_isSaved) {
            changeJob(_job->getNextJob());
        }

    }

}

void Lemming::render() {
    glm::vec2 oldPosition = _job->sprite()->getPosition();
    _job->sprite()->setPosition(oldPosition - Level::currentLevel().getLevelAttributes()->cameraPos);
    _job->sprite()->render();
    _job->sprite()->setPosition(oldPosition);

    _countdown.render();
}

void Lemming::changeJob(Jobs nextJob) {
    glm::ivec2 oldPosition;
    if(_job) {
        walkingRight = _job->isWalkingRight();
        oldPosition = _job->sprite()->getPosition();
        delete _job;
    }
    _job = JobFactory::createJob(nextJob);
    if(_job == nullptr)
        return;

    _job->initAnims(*shaderProgram);
    _job->setWalkingRight(walkingRight);
    _job->sprite()->setPosition(oldPosition);
}

glm::vec2 Lemming::getPosition() const {
    return _job->sprite()->getPosition();
}

Job *Lemming::getJob() {
    return _job;
}

bool Lemming::dead() const {
    return !_alive;
}

bool Lemming::saved() const {
    return _isSaved;
}

bool Lemming::isWalkingRight() const {
    return walkingRight;
}

void Lemming::setWalkingRight(bool value) {
    walkingRight = value;
    _job->setWalkingRight(value);
}

void Lemming::writeDestiny(int deltaTime) {
    _countdown.start(deltaTime);
}

bool Lemming::outOfMap() {
    return !Utils::insideRectangle(_job->sprite()->getPosition(), glm::vec2(0, 0),
                                   glm::vec2(Level::currentLevel().getLevelAttributes()->levelSize.x,
                                             Level::currentLevel().getLevelAttributes()->levelSize.y));
}