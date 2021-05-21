#ifndef _KEYFACTORY_INCLUDE
#define _KEYFACTORY_INCLUDE

#include "Sprite.h"


class KeyFactory {

public:

    static std::unique_ptr<Sprite> createLeftKey(glm::ivec2 size = glm::ivec2(31, 18));

    static std::unique_ptr<Sprite> createRightKey(glm::ivec2 size = glm::ivec2(31, 18));

    static std::unique_ptr<Sprite> createEscapeKey(glm::ivec2 size = glm::ivec2(31, 18));

};


#endif // _KEYFACTORY_INCLUDE

