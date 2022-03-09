#include <iostream>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include "Sprite.h"

Sprite::~Sprite() {
    animations_.clear();
    rotated_.clear();
}

std::unique_ptr<Sprite>
Sprite::createSprite(const glm::vec2 &quadSize, const glm::vec2 &sizeInSpritesheet, ShaderProgram *program,
                     Texture *spriteSheet, Texture *rotatedSpriteSheet) {
    auto quad = std::make_unique<Sprite>(quadSize, sizeInSpritesheet, program, spriteSheet, rotatedSpriteSheet);

    return quad;
}


Sprite::Sprite(const glm::vec2 &quadSize, const glm::vec2 &sizeInSpriteSheet, ShaderProgram *program,
               Texture *spriteSheetPar, Texture *rotatedSpriteSheet) :
        vao_(0),
        vbo_(0),
        pos_(glm::vec2(0.f)),
        texCoordDispl_(glm::vec2(0.f)),
        spriteSheet_(spriteSheetPar),
        rotatedSpriteSheet_(rotatedSpriteSheet),
        shaderProgram_(program),
        currentAnimation_(-1),
        iterated_(false),
        currentKeyframe_(0),
        timeAnimation_(0.0f) {
    float vertices[24] = {0.f, 0.f, 0.f, 0.f,
                          quadSize.x, 0.f, sizeInSpriteSheet.x, 0.f,
                          quadSize.x, quadSize.y, sizeInSpriteSheet.x, sizeInSpriteSheet.y,
                          0.f, 0.f, 0.f, 0.f,
                          quadSize.x, quadSize.y, sizeInSpriteSheet.x, sizeInSpriteSheet.y,
                          0.f, quadSize.y, 0.f, sizeInSpriteSheet.y};

    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);
    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), vertices, GL_STATIC_DRAW);
    this->posLocation_ = program->bindVertexAttribute("position", 2, 4 * sizeof(float), nullptr);
    this->texCoordLocation_ = program->bindVertexAttribute("texCoord", 2, 4 * sizeof(float),
                                                           (void *) (2 * sizeof(float)));
}

int Sprite::update(int deltaTime) {
    int frames = 0;

    if (currentAnimation_ >= 0) {
        bool lastFrame = isInLastFrame();

        timeAnimation_ += static_cast<float>(deltaTime);
        while (timeAnimation_ > animations_[currentAnimation_].milliSecsPerKeyframe) {
            timeAnimation_ -= animations_[currentAnimation_].milliSecsPerKeyframe;
            currentKeyframe_ = (currentKeyframe_ + 1) % animations_[currentAnimation_].keyframeDispl.size();
            frames++;
        }
        texCoordDispl_ = animations_[currentAnimation_].keyframeDispl[currentKeyframe_];

        if (lastFrame && !isInLastFrame()) {
            iterated_ = true;
        }
    }

    return frames;
}

void Sprite::render() const {
    glm::mat4 modelview = glm::translate(glm::mat4(1.0f), glm::vec3(pos_.x, pos_.y, 0.f));
    shaderProgram_->setUniformMatrix4f("modelview", modelview);
    shaderProgram_->setUniform2f("texCoordDispl", texCoordDispl_.x, texCoordDispl_.y);
    glEnable(GL_TEXTURE_2D);
    shaderProgram_->setTextureUnit("tex", 0);
    glActiveTexture(GL_TEXTURE0);
    if (currentAnimation_ < 0 || currentAnimation_ >= rotated_.size()) {
        spriteSheet_->use();
    } else {
        rotated_[currentAnimation_] ? rotatedSpriteSheet_->use() : spriteSheet_->use();
    }
    glBindVertexArray(vao_);
    glEnableVertexAttribArray(posLocation_);
    glEnableVertexAttribArray(texCoordLocation_);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisable(GL_TEXTURE_2D);
}

void Sprite::free() {
    glDeleteBuffers(1, &vbo_);
}

void Sprite::setNumberAnimations(int nAnimations) {
    animations_.clear();
    animations_.resize(nAnimations);

    rotated_.clear();
    rotated_.resize(nAnimations);
}

void Sprite::setAnimationSpeed(int animId, int keyframesPerSec) {
    if (animId < int(animations_.size()))
        animations_[animId].milliSecsPerKeyframe = 1000.f / static_cast<float>(keyframesPerSec);
}

void Sprite::addKeyframe(int animId, const glm::vec2 &displacement, bool isRotated) {
    if (animId < int(animations_.size())) {
        animations_[animId].keyframeDispl.push_back(displacement);
        rotated_[animId] = isRotated;
    }

}

void Sprite::changeAnimation(int animId) {
    if (animId < int(animations_.size())) {
        currentAnimation_ = animId;
        currentKeyframe_ = 0;
        iterated_ = false;
        timeAnimation_ = 0.f;
        texCoordDispl_ = animations_[animId].keyframeDispl[0];
    }
}

std::size_t Sprite::animation() const {
    return currentAnimation_;
}

bool Sprite::isInLastFrame() const {
    return animations_[currentAnimation_].keyframeDispl.size() - 1 == currentKeyframe_;
}

bool Sprite::isInFirstFrame() const {
    return currentKeyframe_ == 0;
}

bool Sprite::hasIterated() const {
    return iterated_;
}

std::size_t Sprite::getAnimationCurrentFrame() const {
    return currentKeyframe_;
}

void Sprite::setPosition(const glm::vec2 &newPos) {
    pos_ = newPos;
}

//glm::vec2 Sprite::position() const {
//    return _pos;
//}

//glm::vec2 &Sprite::position() {
//    return _pos;
//}

void Sprite::setIterated(bool isIterated) {
    iterated_ = isIterated;
}


