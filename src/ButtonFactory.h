#ifndef _BUTTONFACTORY_INCLUDE
#define _BUTTONFACTORY_INCLUDE

#include <glm/glm.hpp>
#include "Button.h"


class ButtonFactory {

public:

    static Button createButton(int buttonName, ShaderManager *shaderManager);

};


#endif // _BUTTONFACTORY_INCLUDE

