#ifndef _PARTICLESYSTEMMANAGER_INCLUDE
#define _PARTICLESYSTEMMANAGER_INCLUDE


#include "ParticleSystem.h"


class ParticleSystemManager {
public:
    explicit ParticleSystemManager(ShaderProgram *shaderProgram);

    void init();

    void createNewParticleSystem(glm::vec2 position);

    void update(int deltaTime);

    void render(glm::vec2 cameraPos);

    bool finished();

private:
    vector<std::unique_ptr<ParticleSystem>> _particleSystems;
    ShaderProgram *_shaderProgram;
};


#endif // _PARTICLESYSTEMMANAGER_INCLUDE


