#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
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
    job = JobFactory::instance().createFallerJob();
    job->initAnims(*shaderProgram);
    job->sprite()->setPosition(initialPosition);
    countdown = nullptr;
    alive = true;
    isSaved = false;
}

void Lemming::update(int deltaTime) {
    if (job->sprite()->update(deltaTime) == 0) {
        return;
    }

    if (outOfMap()) {
        alive = false;
        delete this->job;
        //lemming no longer has a job
        return;
    }
    if (countdown != nullptr && countdown->isOver()) {
        changeJob(JobFactory::instance().createExploderJob());
        delete countdown;
        countdown = nullptr;
        return;
    }
    //still not nuked
    job->updateStateMachine(deltaTime);

    if (countdown != nullptr) {
        //countdown for nuke is running
        countdown->setPosition(glm::vec2(6, -8) + this->job->sprite()->getPosition());
        countdown->update(deltaTime);
    }

    if (job->finished()) {
        if (job->getNextJob() == nullptr) {
            if (job->getCurrentJob() == Jobs::ESCAPER) {
                isSaved = true;
            } else {
                cout << "is finished but not alive" << endl;
                alive = false;
            }
        }
        if (alive && !isSaved) {
            changeJob(job->getNextJob());
        }
    }

}

void Lemming::render() {
    glm::vec2 oldPosition = this->job->sprite()->getPosition();
    this->job->sprite()->setPosition(oldPosition - Level::currentLevel().getLevelAttributes()->cameraPos);
    this->job->sprite()->render();
    this->job->sprite()->setPosition(oldPosition);

    if (countdown != nullptr) {
        countdown->render();
    }
}

void Lemming::changeJob(Job *nextJob) {
    walkingRight = job->isWalkingRight();
    glm::ivec2 oldPosition = this->job->sprite()->getPosition();
    delete this->job;
    this->job = nextJob;
    this->job->initAnims(*shaderProgram);
    nextJob->setWalkingRight(walkingRight);
    this->job->sprite()->setPosition(oldPosition);
}

glm::vec2 Lemming::getPosition() const {
    return this->job->sprite()->getPosition();
}

Job *Lemming::getJob() {
    return job;
}

bool Lemming::dead() const {
    return !alive;
}

bool Lemming::saved() const {
    return isSaved;
}

bool Lemming::isWalkingRight() const {
    return walkingRight;
}

void Lemming::setWalkingRight(bool value) {
    walkingRight = value;
    job->setWalkingRight(value);
}

void Lemming::writeDestiny() {
    countdown = new Countdown();
}

bool Lemming::outOfMap() {
    return !Utils::insideRectangle(this->job->sprite()->getPosition(), glm::vec2(0, 0),
                                   glm::vec2(Level::currentLevel().getLevelAttributes()->levelSize.x,
                                             Level::currentLevel().getLevelAttributes()->levelSize.y));
}