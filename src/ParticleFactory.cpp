#include "ParticleFactory.h"
#include <random>

std::unique_ptr<Particle> ParticleFactory::createParticle(ShaderProgram* shaderProgram) {

    int color = rand() % 3;

    switch (color) {
        case 0:
            return std::make_unique<Particle>(Particle::ParticleColor::BLUE, shaderProgram);
        case 1:
            return std::make_unique<Particle>(Particle::ParticleColor::GREEN, shaderProgram);

        case 2:
            return std::make_unique<Particle>(Particle::ParticleColor::PINK, shaderProgram);

        default:
            return nullptr;
    }
}

