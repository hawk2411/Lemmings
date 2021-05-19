#ifndef _SPRITE_INCLUDE
#define _SPRITE_INCLUDE


#include <vector>
#include <glm/glm.hpp>
#include <memory>
#include "Texture.h"
#include "ShaderProgram.h"
#include "AnimKeyframes.h"
#include "Difficulty.h"


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

    void changeAnimation(Difficulty::Mode mode);

    int animation() const;

    int getAnimationCurrentFrame() const;

    bool isInLastFrame() const;

    bool isInFirstFrame() const;

    bool hasIterated() const;

    void setPosition(const glm::vec2 &newPos);

    //glm::vec2 position() const;
    glm::vec2 getPosition() const {return _pos;}
    glm::vec2 incPosition(glm::vec2 v){
        _pos += v;
        return _pos;
    }
    glm::vec2 decPosition(glm::vec2 v){
        _pos -= v;
        return _pos;
    }

    //glm::vec2 &position();

    void setIterated(bool isIterated);

private:
    const Texture *const _spriteSheet;
    const Texture *const _rotatedSpriteSheet;
    ShaderProgram *shaderProgram;
    GLuint vao;
    GLuint vbo;
    GLint posLocation, texCoordLocation;
    glm::vec2 _pos;
    int currentAnimation, currentKeyframe;
    float timeAnimation;
    glm::vec2 texCoordDispl;
    vector<AnimKeyframes> animations;
    vector<bool> _rotated;
    bool iterated;

};


#endif // _SPRITE_INCLUDE

