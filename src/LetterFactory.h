#ifndef _LETTERFACTORY_INCLUDE
#define _LETTERFACTORY_INCLUDE

#include "Sprite.h"


class LetterFactory {

public:

    static unique_ptr<Sprite> createLetter(char c, ShaderManager *shaderManager);

};


#endif // _LETTERFACTORY_INCLUDE

