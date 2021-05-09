#ifndef _KEYFACTORY_INCLUDE
#define _KEYFACTORY_INCLUDE

#include "Sprite.h"


class KeyFactory {

public:

    static KeyFactory &instance() {
        static KeyFactory instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    };

    std::unique_ptr<Sprite> createLeftKey(glm::ivec2 size = glm::ivec2(31, 18));

    std::unique_ptr<Sprite> createRightKey(glm::ivec2 size = glm::ivec2(31, 18));

    std::unique_ptr<Sprite> createEscapeKey(glm::ivec2 size = glm::ivec2(31, 18));

};


#endif // _KEYFACTORY_INCLUDE

