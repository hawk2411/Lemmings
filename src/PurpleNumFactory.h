#ifndef _PURPLENUMFACTORY_INCLUDE
#define _PURPLENUMFACTORY_INCLUDE

#include "ShaderManager.h"

class PurpleNumFactory {

public:
    static unique_ptr<Sprite> createNum(ShaderManager *shaderManager);

    static unique_ptr<Sprite> createSymbol(char symbol, ShaderManager *shaderManager);

};


#endif // _PURPLENUMFACTORY_INCLUDE

