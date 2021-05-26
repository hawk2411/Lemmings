#ifndef _KEYFACTORY_INCLUDE
#define _KEYFACTORY_INCLUDE

#include "Sprite.h"


class KeyFactory {

public:

    static unique_ptr<Sprite> createLeftKey(ShaderProgram *shaderProgram, glm::ivec2 size = glm::ivec2(31, 18));

    static unique_ptr<Sprite> createRightKey(ShaderProgram *shaderProgram, glm::ivec2 size = glm::ivec2(31, 18));

    static std::unique_ptr<Sprite> createEscapeKey(ShaderProgram *shaderProgram, glm::ivec2 size = glm::ivec2(31, 18));

};


#endif // _KEYFACTORY_INCLUDE

