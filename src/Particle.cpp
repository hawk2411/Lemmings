#include "Particle.h"
#include "ShaderManager.h"
#include "Game.h"
#include <ctime>
#include <random>
#include <math.h>

#define PI 3.14159265359

Particle::Particle(ParticleColor color, ShaderProgram* shaderProgram):_position(0,0), _speed(0,0) {
    glm::vec2 coordTex;
    switch (color) {
        case PINK:
            coordTex = glm::vec2(0, 0);
            break;
        case BLUE:
            coordTex = glm::vec2(0.5, 0);
            break;
        case GREEN:
            coordTex = glm::vec2(0.25, 0);
            break;
        default:
            coordTex = glm::vec2(0, 0);
    }
    _sprite = Sprite::createSprite(glm::ivec2(1, 1), glm::vec2(0.25, 1.),
                                   shaderProgram,
                                   &Game::spriteSheets().particleSprites);
    _sprite->setNumberAnimations(1);
    _sprite->addKeyframe(0, coordTex);
    _sprite->changeAnimation(0);

    float angle = (rand() % 180) * PI / 180;
    _speed = glm::vec2(2.5 * cos(angle), -5 * sin(angle));
}

void Particle::setPosition(glm::vec2 position) {
    _position = position;
}

void Particle::update(int deltaTime) {
    _position += _speed;
    _sprite->setPosition(_position);
    _speed += glm::vec2(0, 0.25);
}

void Particle::render(glm::vec2 cameraPos) {
    glm::vec2 oldPosition = _sprite->getPosition();
    _sprite->setPosition(oldPosition - cameraPos);
    _sprite->render();
    _sprite->setPosition(oldPosition);
}