#include "ParticleSystemManager.h"
#include <ctime>
#include <random>


void ParticleSystemManager::init() {
    particleSystems.clear();
    particleSystems.resize(0);
}

void ParticleSystemManager::createNewParticleSystem( ShaderProgram* shaderProgram, glm::vec2 position) {

    ParticleSystem *particleSystem = new ParticleSystem(shaderProgram);
    particleSystem->setPosition(position);
    particleSystems.push_back(particleSystem);
}

void ParticleSystemManager::update(int deltaTime) {
    for (int i = 0; i < particleSystems.size(); ++i) {
        if (particleSystems[i]->notFinished()) {
            particleSystems[i]->update(deltaTime);
        }
    }
}

void ParticleSystemManager::render(glm::vec2 cameraPos) {
    for (int i = 0; i < particleSystems.size(); ++i) {
        if (particleSystems[i]->notFinished()) {
            particleSystems[i]->render(cameraPos);
        }
    }
}

bool ParticleSystemManager::finished() {
    bool finished = true;
    for (int i = 0; i < particleSystems.size(); ++i) {
        if (particleSystems[i]->notFinished()) {
            finished = false;
        }
    }
    return finished;
}