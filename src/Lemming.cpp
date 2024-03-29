#include "Lemming.h"
#include "ShaderManager.h"
#include "JobFactory.h"
#include "Utils.h"
#include "IMaskManager.h"

Lemming::Lemming(const glm::vec2 &initialPosition, ShaderManager *shaderManager, ParticleSystemManager* particleSystemManager)
        : _shaderManager(shaderManager), _countdown(shaderManager), _particleSystemManager(particleSystemManager) {
    _job = JobFactory::createJob(Jobs::FALLER,  _particleSystemManager);
    _job->initAnims(_shaderManager->getShaderProgram());
    _position = initialPosition;
    _job->sprite()->setPosition(_position);
    _alive = true;
    _isSaved = false;
}

void Lemming::update(int deltaTime, Level *levelAttributes, IMaskManager *mask) {
    if (_job->sprite()->update(deltaTime) == 0) {
        return;
    }

    if (outOfMap(levelAttributes->levelSize)) {
        _alive = false;
        _job.reset(nullptr);
        //lemming no longer has a job
        return;
    }
    if (_countdown.isStarted() && _countdown.isOver()) {
        changeJob(Jobs::EXPLODER);
        _countdown.reset();
    }
    else {
        //still not nuked
        _job->updateStateMachine(deltaTime, levelAttributes, mask);

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
                    _alive = false;
                }
            }
            if (_alive && !_isSaved) {
                changeJob(_job->getNextJob());
            }

        }
    }

}

void Lemming::render(const glm::vec2 &cameraPos) {
    glm::vec2 oldPosition = _job->sprite()->getPosition();
    _job->sprite()->setPosition(oldPosition - cameraPos);
    _job->sprite()->render();
    _job->sprite()->setPosition(oldPosition);

    _countdown.render(cameraPos);
}

void Lemming::changeJob(Jobs nextJob) {
    if(_job != nullptr && _job->getCurrentJob() == nextJob) {
        //not necessary to create the same job.
        return;
    }
    glm::ivec2 oldPosition;
    if(_job) {
        walkingRight = _job->isWalkingRight();
        oldPosition = _job->sprite()->getPosition();
        _job.reset(nullptr);
    }
    _job = JobFactory::createJob(nextJob, _particleSystemManager);
    if(!_job)
        return;

    _job->initAnims(_shaderManager->getShaderProgram());
    _job->setWalkingRight(walkingRight);
    _job->sprite()->setPosition(oldPosition);
}

glm::vec2 Lemming::getPosition() const {
    return _job->sprite()->getPosition();
}

Job *Lemming::getJob() {
    return _job.get();
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

bool Lemming::outOfMap(const glm::vec2 &levelSize)const {
    return !Utils::insideRectangle(_job->sprite()->getPosition(), glm::vec2(0, 0), levelSize);
}
