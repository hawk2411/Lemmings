#include "ParticleSystem.h"
#include "ParticleFactory.h"

ParticleSystem::ParticleSystem(ShaderProgram *shaderProgram) {
    _alive = true;

    int numParticles = std::rand() % 16 + 10;
    for (int i = 0; i < numParticles; ++i) {
        _particles.push_back(std::unique_ptr<Particle>(ParticleFactory::createParticle(shaderProgram)));
    }
}

void ParticleSystem::setPosition(glm::vec2 position) {
    for (auto &particle : _particles) {
        particle->setPosition(position);
    }
}


void ParticleSystem::update(int deltaTime) {
    _currentTime += static_cast<float>(deltaTime);
    if (_currentTime / 1000 > 2) {
        _alive = false;
        return;
    }
    for (auto &particle : _particles) {
        particle->update();
    }
}

void ParticleSystem::render(glm::vec2 cameraPos) {
    for (auto &particle : _particles) {
        particle->render(cameraPos);
    }
}

bool ParticleSystem::notFinished() const {
    return _alive;
}
