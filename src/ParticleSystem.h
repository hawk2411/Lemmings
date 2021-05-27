#ifndef _PARTICLESYSTEM_INCLUDE
#define _PARTICLESYSTEM_INCLUDE


#include "Particle.h"


class ParticleSystem {
public:
    ParticleSystem( ShaderProgram* shaderProgram);

    void setPosition(glm::vec2 position);

    void update(int deltaTime);

    void render(glm::vec2 cameraPos);

    bool notFinished() const;

private:
    vector<Particle *> _particles;
    int numParticles;
    float _currentTime = 0.f;
    bool _alive;
};


#endif // _PARTICLESYSTEM_INCLUDE


