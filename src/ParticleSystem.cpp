#include "ParticleSystem.h"
#include "ParticleFactory.h"
#include <ctime>
#include <random>

ParticleSystem::ParticleSystem( ShaderProgram* shaderProgram) {
    alive = true;

    numParticles = rand() % 16 + 10;
    particles.resize(numParticles);

    for (int i = 0; i < numParticles; ++i) {
        particles[i] = ParticleFactory::createParticle(shaderProgram);
    }
}

void ParticleSystem::setPosition(glm::vec2 position) {
    for (int i = 0; i < numParticles; ++i) {
        particles[i]->setPosition(position);
    }
}


void ParticleSystem::update(int deltaTime) {
    currentTime += deltaTime;
    if (currentTime / 1000 > 2) {
        alive = false;
    } else {
        for (int i = 0; i < numParticles; ++i) {
            particles[i]->update(deltaTime);
        }
    }

}

void ParticleSystem::render(glm::vec2 cameraPos) {
    for (int i = 0; i < numParticles; ++i) {
        particles[i]->render(cameraPos);
    }
}

bool ParticleSystem::notFinished() const {
    return alive;
}
