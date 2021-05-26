#ifndef _BUTTONNUMFACTORY_INCLUDE
#define _BUTTONNUMFACTORY_INCLUDE
#include <memory>
#include "Sprite.h"
#include "ShaderManager.h"


class ButtonNumFactory {
public:
    static std::unique_ptr<Sprite> createNum(ShaderManager* shaderManager);
};


#endif // _BUTTONNUMFACTORY_INCLUDE

