#include "Job.h"

Job::Job() : _isFinished(false), _currentJob(Jobs::UNKNOWN), _nextJob(Jobs::UNKNOWN), _walkingRight(true) {}

Job::Job(Jobs currentJob) : _isFinished(false), _currentJob(currentJob), _nextJob(Jobs::UNKNOWN), _walkingRight(true) {
}

Job::~Job() = default;

int Job::collisionFloor(int maxFall, const VariableTexture &maskedMap) const {
    bool bContact = false;
    int fall = 0;
    glm::ivec2 posBase = _jobSprite->getPosition();

    posBase += glm::ivec2(7, 16);
    while ((fall < maxFall) && !bContact) {
        if ((maskedMap.pixel(posBase.x, posBase.y + fall) == 0) &&
            (maskedMap.pixel(posBase.x + 1, posBase.y + fall) == 0))
            fall += 1;
        else
            bContact = true;
    }

    return fall;
}

bool Job::collision(const VariableTexture &maskedMap) const {
    glm::ivec2 posBase = _jobSprite->getPosition();

    posBase += glm::ivec2(7, 15);
    if ((maskedMap.pixel(posBase.x, posBase.y) == 0) &&
        (maskedMap.pixel(posBase.x + 1, posBase.y) == 0))
        return false;

    return true;
}


bool Job::finished() const {
    return _isFinished;
}

Jobs Job::getNextJob() const {
    return _nextJob;
}


Sprite *Job::sprite() {
    return _jobSprite.get();
}

void Job::setWalkingRight(bool value) {
    _walkingRight = value;
}

bool Job::isWalkingRight() const {
    return _walkingRight;
}
