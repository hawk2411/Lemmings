#ifndef _PREDEFINEDWORDFACTORY_INCLUDE
#define _PREDEFINEDWORDFACTORY_INCLUDE

#include <glm/glm.hpp>
#include "Button.h"
#include "ShaderManager.h"

class PredefinedWordFactory {

public:
    enum JobNames {
        WALKER,
        MINER,
        FLOATER,
        FALLER,
        DIGGER,
        CLIMBER,
        BUILDER,
        BLOCKER,
        BASHER,
        NONE
    };

    static unique_ptr<Sprite> createJobWord(ShaderProgram *shaderProgram);

    static unique_ptr<Sprite> createInfoWord(const string &infoWord, ShaderProgram *shaderProgram);

};


#endif // _PREDEFINEDWORDFACTORY_INCLUDE

