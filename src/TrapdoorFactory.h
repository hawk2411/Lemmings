#ifndef _TRAPDOORFACTORY_INCLUDE
#define _TRAPDOORFACTORY_INCLUDE

#include "Sprite.h"
#include "Trapdoor.h"
#include "ShaderManager.h"

class TrapdoorFactory {

public:
    static std::unique_ptr<Trapdoor> createTrapdoor(const string &type, ShaderManager *shaderManager);

};


#endif // _TRAPDOORFACTORY_INCLUDE

