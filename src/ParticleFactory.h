#ifndef _PARTICLEFACTORY_INCLUDE
#define _PARTICLEFACTORY_INCLUDE

#include "Particle.h"


class ParticleFactory {

public:

    static Particle *createParticle( ShaderProgram* shaderProgram);

};


#endif // _PARTICLEFACTORY_INCLUDE

