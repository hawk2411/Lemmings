#ifndef _PARTICLEFACTORY_INCLUDE
#define _PARTICLEFACTORY_INCLUDE

#pragma once
#include "Particle.h"


class ParticleFactory {

public:

    static std::unique_ptr<Particle> createParticle( ShaderProgram* shaderProgram);

};


#endif // _PARTICLEFACTORY_INCLUDE

