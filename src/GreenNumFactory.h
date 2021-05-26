#ifndef _GREENNUMFACTORY_INCLUDE
#define _GREENNUMFACTORY_INCLUDE
#include "ShaderManager.h"

class GreenNumFactory {

public:

    static unique_ptr<Sprite> createNum(ShaderManager *shaderManager);

    static unique_ptr<Sprite> createSymbol(char symbol, ShaderManager *shaderManager);

};


#endif // _GREENNUMFACTORY_INCLUDE

