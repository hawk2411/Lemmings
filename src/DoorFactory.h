#ifndef _DOORFACTORY_INCLUDE
#define _DOORFACTORY_INCLUDE

#include "Sprite.h"
#include "Door.h"
#include "ShaderManager.h"

class DoorFactory {

public:
    static std::unique_ptr<Door> createDoor(const string &type, ShaderManager *shaderManager);
};


#endif // _DOORFACTORY_INCLUDE

