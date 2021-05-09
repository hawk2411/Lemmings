#ifndef _PARTICLE_INCLUDE
#define _PARTICLE_INCLUDE

#include "Sprite.h"
#include <glm/glm.hpp>


class Particle {

public:
    enum ParticleColor {
        BLUE,
        GREEN,
        PINK
    };

    Particle() {};

    Particle(ParticleColor color);

    void setPosition(glm::vec2 position);

    void update(int deltaTime);

    void render();

private:
    std::unique_ptr<Sprite> sprite;
    glm::vec2 position;
    glm::vec2 speed;
};


#endif // _PARTICLE_INCLUDE


