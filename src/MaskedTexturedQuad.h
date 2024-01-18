#ifndef _MASKED_TEXTURED_QUAD_INCLUDE
#define _MASKED_TEXTURED_QUAD_INCLUDE


#include <glm/glm.hpp>
#include <memory>
#include <iostream>
#include "Texture.h"
#include "VariableTexture.h"
#include "ShaderProgram.h"


class MaskedTexturedQuad {

public:
    MaskedTexturedQuad(glm::vec2 geom[2], glm::vec2 texCoords[2], ShaderProgram &program);

    void render(ShaderProgram &program, const Texture &tex, const VariableTexture &mask) const;

    // Textured quads can only be created inside an OpenGL context
    static unique_ptr<MaskedTexturedQuad>

    createTexturedQuad(glm::vec2 geom[2], glm::vec2 texCoords[2], ShaderProgram &program);

private:
    GLuint _vao;
    GLuint _vbo;
    GLint _posLocation, _texCoordLocation;

};


#endif // _MASKED_TEXTURED_QUAD_INCLUDE

