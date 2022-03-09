#ifndef _SPRITE_INCLUDE
#define _SPRITE_INCLUDE


#include <vector>
#include <glm/glm.hpp>
#include <memory>
#include "Texture.h"
#include "ShaderProgram.h"
#include "AnimKeyframes.h"
#include "LevelModes.h"


// This class is derived from code seen earlier in TexturedQuad but it is also
// able to manage animations stored as a spritesheet. 


class Sprite {

    /*
     * factory functions
     */
public:
    // Textured quads can only be created inside an OpenGL context
    static std::unique_ptr<Sprite>
    createSprite(const glm::vec2 &quadSize, const glm::vec2 &sizeInSpritesheet, ShaderProgram *program,
                 Texture *spriteSheet, Texture *rotatedSpriteSheet = nullptr);

public:
    Sprite(const glm::vec2 &quadSize, const glm::vec2 &sizeInSpriteSheet, ShaderProgram *program, Texture *spriteSheet,
           Texture *rotatedSpriteSheet);

    ~Sprite();

    int update(int deltaTime);

    void render() const;

    void free();

    void setNumberAnimations(int nAnimations);

    void setAnimationSpeed(int animId, int keyframesPerSec);

    void addKeyframe(int animId, const glm::vec2 &frame, bool isRotated = false);

    void changeAnimation(int animId);

    std::size_t animation() const;

    std::size_t getAnimationCurrentFrame() const;

    bool isInLastFrame() const;

    bool isInFirstFrame() const;

    bool hasIterated() const;

    void setPosition(const glm::vec2 &newPos);

    //glm::vec2 position() const;
    glm::vec2 getPosition() const {return pos_;}
    glm::vec2 incPosition(glm::vec2 v){
        pos_ += v;
        return pos_;
    }
    glm::vec2 decPosition(glm::vec2 v){
        pos_ -= v;
        return pos_;
    }

    //glm::vec2 &position();

    void setIterated(bool isIterated);

private:
    const Texture *const spriteSheet_;
    const Texture *const rotatedSpriteSheet_;
    ShaderProgram *shaderProgram_;
    GLuint vao_;
    GLuint vbo_;
    GLint posLocation_, texCoordLocation_;
    glm::vec2 pos_;
    std::size_t currentAnimation_, currentKeyframe_;
    float timeAnimation_;
    glm::vec2 texCoordDispl_;
    vector<AnimKeyframes> animations_;
    vector<bool> rotated_;
    bool iterated_;

};


#endif // _SPRITE_INCLUDE

