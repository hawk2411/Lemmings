#include <fstream>
#include "Shader.h"


using namespace std;


Shader::Shader() {
    _shaderId = 0;
    _compiled = false;
}


void Shader::initFromSource(const ShaderType type, const string &source) {
    const char *sourcePtr = source.c_str();
    GLint status;
    char buffer[512];

    switch (type) {
        case VERTEX_SHADER:
            _shaderId = glCreateShader(GL_VERTEX_SHADER);
            break;
        case FRAGMENT_SHADER:
            _shaderId = glCreateShader(GL_FRAGMENT_SHADER);
            break;
    }
    if (_shaderId == 0)
        return;
    glShaderSource(_shaderId, 1, &sourcePtr, nullptr);
    glCompileShader(_shaderId);
    glGetShaderiv(_shaderId, GL_COMPILE_STATUS, &status);
    _compiled = (status == GL_TRUE);
    glGetShaderInfoLog(_shaderId, 512, nullptr, buffer);
    _errorLog.assign(buffer);
}

bool Shader::initFromFile(const ShaderType type, const string &filename) {
    string shaderSource;

    if (!loadShaderSource(filename, shaderSource))
        return false;
    initFromSource(type, shaderSource);

    return true;
}

void Shader::free() {
    glDeleteShader(_shaderId);
    _shaderId = 0;
    _compiled = false;
}

GLuint Shader::getId() const {
    return _shaderId;
}

bool Shader::isCompiled() const {
    return _compiled;
}

const string &Shader::log() const {
    return _errorLog;
}

bool Shader::loadShaderSource(const string &filename, string &shaderSource) {
    ifstream fin;

    fin.open(filename.c_str());
    if (!fin.is_open())
        return false;
    shaderSource.assign(istreambuf_iterator<char>(fin), istreambuf_iterator<char>());

    return true;
}

