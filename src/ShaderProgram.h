#ifndef _SHADER_PROGRAM_INCLUDE
#define _SHADER_PROGRAM_INCLUDE


#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include "Shader.h"


// Using the Shader class ShaderProgram can link a vertex and a fragment shader
// together, bind input attributes to their corresponding vertex shader names, 
// and bind the fragment output to a name from the fragment shader


class ShaderProgram {

public:
    ShaderProgram();

    void init();

    void addShader(const Shader &shader) const;

    void bindFragmentOutput(const string &outputName) const;

    GLint bindVertexAttribute(const string &attribName, GLint size, GLsizei stride, GLvoid *firstPointer) const;

    void link();

    void free() const;

    void use() const;

    // Pass uniforms to the associated shaders
    void setUniform2f(const string &uniformName, float v0, float v1) const;

    void setUniform3f(const string &uniformName, float v0, float v1, float v2) const;

    void setUniform4f(const string &uniformName, float v0, float v1, float v2, float v3) const;

    void setUniformMatrix4f(const string &uniformName, glm::mat4 &mat) const;

    void setTextureUnit(const string &uniformName, int unit) const;

    bool isLinked() const;

    const string &log() const;

private:
    GLuint _programId;
    bool _linked;
    string _errorLog;

};


#endif // _SHADER_PROGRAM_INCLUDE
