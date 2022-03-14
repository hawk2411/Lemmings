#include "ParticleFactory.h"
#include <random>

Particle *ParticleFactory::createParticle(ShaderProgram* shaderProgram) {

    int color = rand() % 3;

    switch (color) {
        case 0:
            return new Particle(Particle::ParticleColor::BLUE, shaderProgram);
        case 1:
            return new Particle(Particle::ParticleColor::GREEN, shaderProgram);

        case 2:
            return new Particle(Particle::ParticleColor::PINK, shaderProgram);

        default:
            return nullptr;
    }
}

