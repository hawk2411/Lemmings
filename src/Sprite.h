#ifndef _SPRITE_INCLUDE
#define _SPRITE_INCLUDE


#include <vector>
#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"
#include "AnimKeyframes.h"


// This class is derived from code seen earlier in TexturedQuad but it is also
// able to manage animations stored as a spritesheet. 


class Sprite
{

public:
	~Sprite();

	// Textured quads can only be created inside an OpenGL context
	static Sprite *createSprite(const glm::vec2 &quadSize, const glm::vec2 &sizeInSpritesheet, ShaderProgram *program, Texture *spritesheet, Texture *rotatedSpritesheet = NULL);

	Sprite(const glm::vec2 &quadSize, const glm::vec2 &sizeInSpritesheet, ShaderProgram *program, Texture *spritesheet, Texture *rotatedSpritesheet);

	int update(int deltaTime);
	void render() const;
	void free();

	void setNumberAnimations(int nAnimations);
	void setAnimationSpeed(int animId, int keyframesPerSec);
	void addKeyframe(int animId, const glm::vec2 &frame, bool rotated = false);
	void changeAnimation(int animId);
	int animation() const;
	int getAnimationCurrentFrame() const;
	bool isInLastFrame() const;
	bool isInFirstFrame() const;
	bool hasIterated() const;

	void setPosition(const glm::vec2 &newPos);
	glm::vec2 position() const;
	glm::vec2 &position();

	void setIterated(bool iterated);

private:
	Texture *texture;
	Texture *spriteSheet;
	Texture *rotatedSpriteSheet;
	ShaderProgram *shaderProgram;
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	glm::vec2 pos;
	int currentAnimation, currentKeyframe;
	float timeAnimation;
	glm::vec2 texCoordDispl;
	vector<AnimKeyframes> animations;
	vector<bool> rotated;
	bool iterated;

};


#endif // _SPRITE_INCLUDE

