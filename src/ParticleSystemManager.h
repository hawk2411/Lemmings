#ifndef _PARTICLESYSTEMMANAGER_INCLUDE
#define _PARTICLESYSTEMMANAGER_INCLUDE


#include "ParticleSystem.h"


class ParticleSystemManager {
public:
    void init();

    void createNewParticleSystem(glm::vec2 position);

    void update(int deltaTime);

    void render();

    bool finished();

private:
    vector<ParticleSystem *> particleSystems;
};


#endif // _PARTICLESYSTEMMANAGER_INCLUDE


