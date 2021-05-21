#ifndef _PARTICLESYSTEM_INCLUDE
#define _PARTICLESYSTEM_INCLUDE


#include "Particle.h"


class ParticleSystem {
public:
    ParticleSystem();

    void setPosition(glm::vec2 position);

    void update(int deltaTime);

    void render(glm::vec2 cameraPos);

    bool notFinished() const;

private:
    vector<Particle *> particles;
    int numParticles;
    float currentTime = 0.f;
    bool alive;
};


#endif // _PARTICLESYSTEM_INCLUDE


