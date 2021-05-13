#ifndef _SHADERMANAGER_INCLUDE
#define _SHADERMANAGER_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "MaskedTexturedQuad.h"


class ShaderManager {

public:
    static ShaderManager &getInstance() {
        static ShaderManager instance;

        return instance;
    }

    void init();

    ShaderProgram &getShaderProgram();

    ShaderProgram &getMaskedShaderProgram();

    void useMaskedShaderProgram();

    void useShaderProgram();

    glm::mat4 getProjectionMatrix();

private:
    ShaderProgram _simpleTexProgram, _maskedTexProgram;
    glm::mat4 _projection;
    glm::mat4 _modelView;
};

#endif //_SHADERMANAGER_INCLUDE

