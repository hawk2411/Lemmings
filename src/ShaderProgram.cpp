#include <glm/gtc/type_ptr.hpp>
#include "ShaderProgram.h"


ShaderProgram::ShaderProgram() {
    _programId = 0;
    _linked = false;
}


void ShaderProgram::init() {
    _programId = glCreateProgram();
}

void ShaderProgram::addShader(const Shader &shader) const {
    glAttachShader(_programId, shader.getId());
}

void ShaderProgram::bindFragmentOutput(const string &outputName) const {
    glBindAttribLocation(_programId, 0, outputName.c_str());
}

GLint
ShaderProgram::bindVertexAttribute(const string &attribName, GLint size, GLsizei stride, GLvoid *firstPointer) const {
    GLint attribPos;

    attribPos = glGetAttribLocation(_programId, attribName.c_str());
    glVertexAttribPointer(attribPos, size, GL_FLOAT, GL_FALSE, stride, firstPointer);

    return attribPos;
}

void ShaderProgram::link() {
    GLint status;
    const GLsizei BUFFER_SIZE = 512;
    char buffer[BUFFER_SIZE];

    glLinkProgram(_programId);
    glGetProgramiv(_programId, GL_LINK_STATUS, &status);
    _linked = (status == GL_TRUE);
    glGetProgramInfoLog(_programId, BUFFER_SIZE, nullptr, buffer);
    _errorLog.assign(buffer);
}

void ShaderProgram::free() const {
    glDeleteProgram(_programId);
}

void ShaderProgram::use() const {
    glUseProgram(_programId);
}

bool ShaderProgram::isLinked() const {
    return _linked;
}

const string &ShaderProgram::log() const {
    return _errorLog;
}

void ShaderProgram::setUniform2f(const string &uniformName, float v0, float v1) const {
    GLint location = glGetUniformLocation(_programId, uniformName.c_str());

    if (location != -1)
        glUniform2f(location, v0, v1);
}

void ShaderProgram::setUniform3f(const string &uniformName, float v0, float v1, float v2) const {
    GLint location = glGetUniformLocation(_programId, uniformName.c_str());

    if (location != -1)
        glUniform3f(location, v0, v1, v2);
}

void ShaderProgram::setUniform4f(const string &uniformName, float v0, float v1, float v2, float v3) const {
    GLint location = glGetUniformLocation(_programId, uniformName.c_str());

    if (location != -1)
        glUniform4f(location, v0, v1, v2, v3);
}

void ShaderProgram::setUniformMatrix4f(const string &uniformName, glm::mat4 &mat) const {
    GLint location = glGetUniformLocation(_programId, uniformName.c_str());

    if (location != -1)
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void ShaderProgram::setTextureUnit(const string &uniformName, int unit) const {
    GLint location = glGetUniformLocation(_programId, uniformName.c_str());
    glUniform1i(location, unit);
}


