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

    //Particle():_position(0,0), _speed(0,0) {};

    explicit Particle(ParticleColor color, ShaderProgram* shaderProgram);

    void setPosition(glm::vec2 position);

    void update(int deltaTime);

    void render(glm::vec2 cameraPos);

private:
    std::unique_ptr<Sprite> _sprite;
    glm::vec2 _position;
    glm::vec2 _speed;
};


#endif // _PARTICLE_INCLUDE


