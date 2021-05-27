#include "ParticleSystem.h"
#include "ParticleFactory.h"
#include <ctime>
#include <random>

ParticleSystem::ParticleSystem( ShaderProgram* shaderProgram) {
    _alive = true;

    numParticles = rand() % 16 + 10;
    for (int i = 0; i < numParticles; ++i) {
        _particles.push_back(std::unique_ptr<Particle>(ParticleFactory::createParticle(shaderProgram)));
    }
}

void ParticleSystem::setPosition(glm::vec2 position) {
    for (int i = 0; i < numParticles; ++i) {
        _particles[i]->setPosition(position);
    }
}


void ParticleSystem::update(int deltaTime) {
    _currentTime += static_cast<float>(deltaTime);
    if (_currentTime / 1000 > 2) {
        _alive = false;
    } else {
        for (int i = 0; i < numParticles; ++i) {
            _particles[i]->update(deltaTime);
        }
    }

}

void ParticleSystem::render(glm::vec2 cameraPos) {
    for (int i = 0; i < numParticles; ++i) {
        _particles[i]->render(cameraPos);
    }
}

bool ParticleSystem::notFinished() const {
    return _alive;
}
