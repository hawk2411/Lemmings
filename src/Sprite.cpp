#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include "Sprite.h"

Sprite::~Sprite() {
    animations.clear();
    _rotated.clear();
}

std::unique_ptr<Sprite>
Sprite::createSprite(const glm::vec2 &quadSize, const glm::vec2 &sizeInSpritesheet, ShaderProgram *program,
                     Texture *spriteSheet, Texture *rotatedSpriteSheet) {
    auto quad = std::make_unique<Sprite>(quadSize, sizeInSpritesheet, program, spriteSheet, rotatedSpriteSheet);

    return quad;
}


Sprite::Sprite(const glm::vec2 &quadSize, const glm::vec2 &sizeInSpriteSheet, ShaderProgram *program,
               Texture *spriteSheetPar, Texture *rotatedSpriteSheet) :
        vao(0),
        vbo(0),
        _pos(glm::vec2(0.f)),
        texCoordDispl(glm::vec2(0.f)),
        _spriteSheet(spriteSheetPar),
        _rotatedSpriteSheet(rotatedSpriteSheet),
        shaderProgram(program),
        currentAnimation(-1),
        iterated(false),
        currentKeyframe(0),
        timeAnimation(0.0f) {
    float vertices[24] = {0.f, 0.f, 0.f, 0.f,
                          quadSize.x, 0.f, sizeInSpriteSheet.x, 0.f,
                          quadSize.x, quadSize.y, sizeInSpriteSheet.x, sizeInSpriteSheet.y,
                          0.f, 0.f, 0.f, 0.f,
                          quadSize.x, quadSize.y, sizeInSpriteSheet.x, sizeInSpriteSheet.y,
                          0.f, quadSize.y, 0.f, sizeInSpriteSheet.y};

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), vertices, GL_STATIC_DRAW);
    this->posLocation = program->bindVertexAttribute("position", 2, 4 * sizeof(float), 0);
    this->texCoordLocation = program->bindVertexAttribute("texCoord", 2, 4 * sizeof(float),
                                                          (void *) (2 * sizeof(float)));
}

int Sprite::update(int deltaTime) {
    int frames = 0;

    if (currentAnimation >= 0) {
        bool lastFrame = isInLastFrame();

        timeAnimation += deltaTime;
        while (timeAnimation > animations[currentAnimation].millisecsPerKeyframe) {
            timeAnimation -= animations[currentAnimation].millisecsPerKeyframe;
            currentKeyframe = (currentKeyframe + 1) % animations[currentAnimation].keyframeDispl.size();
            frames++;
        }
        texCoordDispl = animations[currentAnimation].keyframeDispl[currentKeyframe];

        if (lastFrame && !isInLastFrame()) {
            iterated = true;
        }
    }

    return frames;
}

void Sprite::render() const {
    glm::mat4 modelview = glm::translate(glm::mat4(1.0f), glm::vec3(_pos.x, _pos.y, 0.f));
    shaderProgram->setUniformMatrix4f("modelview", modelview);
    shaderProgram->setUniform2f("texCoordDispl", texCoordDispl.x, texCoordDispl.y);
    glEnable(GL_TEXTURE_2D);
    shaderProgram->setTextureUnit("tex", 0);
    glActiveTexture(GL_TEXTURE0);
    const Texture *current = _spriteSheet;
    if (currentAnimation < 0 || currentAnimation >= _rotated.size()) {
        _spriteSheet->use();
    } else {
        _rotated[currentAnimation] ? _rotatedSpriteSheet->use() : _spriteSheet->use();
    }
    glBindVertexArray(vao);
    glEnableVertexAttribArray(posLocation);
    glEnableVertexAttribArray(texCoordLocation);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisable(GL_TEXTURE_2D);
}

void Sprite::free() {
    glDeleteBuffers(1, &vbo);
}

void Sprite::setNumberAnimations(int nAnimations) {
    animations.clear();
    animations.resize(nAnimations);

    _rotated.clear();
    _rotated.resize(nAnimations);
}

void Sprite::setAnimationSpeed(int animId, int keyframesPerSec) {
    if (animId < int(animations.size()))
        animations[animId].millisecsPerKeyframe = 1000.f / keyframesPerSec;
}

void Sprite::addKeyframe(int animId, const glm::vec2 &displacement, bool isRotated) {
    if (animId < int(animations.size())) {
        animations[animId].keyframeDispl.push_back(displacement);
        _rotated[animId] = isRotated;
    }

}

void Sprite::changeAnimation(int animId) {
    if (animId < int(animations.size())) {
        currentAnimation = animId;
        currentKeyframe = 0;
        iterated = false;
        timeAnimation = 0.f;
        texCoordDispl = animations[animId].keyframeDispl[0];
    }
}

int Sprite::animation() const {
    return currentAnimation;
}

bool Sprite::isInLastFrame() const {
    return animations[currentAnimation].keyframeDispl.size() - 1 == currentKeyframe;
}

bool Sprite::isInFirstFrame() const {
    return currentKeyframe == 0;
}

bool Sprite::hasIterated() const {
    return iterated;
}

int Sprite::getAnimationCurrentFrame() const {
    return currentKeyframe;
}

void Sprite::setPosition(const glm::vec2 &newPos) {
    _pos = newPos;
}

//glm::vec2 Sprite::position() const {
//    return _pos;
//}

//glm::vec2 &Sprite::position() {
//    return _pos;
//}

void Sprite::setIterated(bool isIterated) {
    iterated = isIterated;
}


