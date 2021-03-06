#ifndef _PARTICLESYSTEM_INCLUDE
#define _PARTICLESYSTEM_INCLUDE

#include "Particle.h"

class ParticleSystem {
public:
    explicit ParticleSystem(ShaderProgram* shaderProgram);

    void setPosition(glm::vec2 position);

    void update(int deltaTime);

    void render(glm::vec2 cameraPos);

    bool notFinished() const;

private:
    vector<std::unique_ptr<Particle>> _particles;
    float _currentTime = 0.f;
    bool _alive;
};


#endif // _PARTICLESYSTEM_INCLUDE


