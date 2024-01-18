#include "ParticleSystemManager.h"
#include <algorithm>

ParticleSystemManager::ParticleSystemManager(ShaderProgram *shaderProgram) : _shaderProgram(shaderProgram) {

}

void ParticleSystemManager::init() {
    _particleSystems.clear();
    //_particleSystems.resize(0);
}

void ParticleSystemManager::createNewParticleSystem(glm::vec2 position) {
    auto particleSystem = std::make_unique<ParticleSystem>(_shaderProgram);
    particleSystem->setPosition(position);
    _particleSystems.push_back(std::move(particleSystem));
}

void ParticleSystemManager::update(int deltaTime) {
    for (auto &_particleSystem : _particleSystems) {
        if (_particleSystem->notFinished()) {
            _particleSystem->update(deltaTime);
        }
    }
}

void ParticleSystemManager::render(glm::vec2 cameraPos) {
    for (auto &_particleSystem : _particleSystems) {
        if (_particleSystem->notFinished()) {
            _particleSystem->render(cameraPos);
        }
    }
}

bool ParticleSystemManager::finished() {
    bool not_finished = std::any_of(_particleSystems.cbegin(), _particleSystems.cend(),
                                    [](const auto &ps) { return ps->notFinished(); });
    return !not_finished;
}