#ifndef _SHADERMANAGER_INCLUDE
#define _SHADERMANAGER_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"



class ShaderManager {

public:
    ShaderManager();


    ShaderProgram &getShaderProgram();

    ShaderProgram &getMaskedShaderProgram();

    void useMaskedShaderProgram();

    void useShaderProgram();

    glm::mat4 getProjectionMatrix();

private:

    ShaderProgram _simpleTexProgram, _maskedTexProgram;
    glm::mat4 _projection{1.0};
    glm::mat4 _modelView{1.0};
};

#endif //_SHADERMANAGER_INCLUDE

