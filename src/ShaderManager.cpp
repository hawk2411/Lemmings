#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "ShaderManager.h"
#include "Shader.h"

ShaderManager::ShaderManager() {
    Shader vShader, fShader;

    vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
    if (!vShader.isCompiled()) {
        cout << "Vertex Shader Error" << endl;
        cout << "" << vShader.log() << endl << endl;
    }
    fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
    if (!fShader.isCompiled()) {
        cout << "Fragment Shader Error" << endl;
        cout << "" << fShader.log() << endl << endl;
    }
    _simpleTexProgram.init();
    _simpleTexProgram.addShader(vShader);
    _simpleTexProgram.addShader(fShader);
    _simpleTexProgram.link();
    if (!_simpleTexProgram.isLinked()) {
        cout << "Shader Linking Error" << endl;
        cout << "" << _simpleTexProgram.log() << endl << endl;
    }
    _simpleTexProgram.bindFragmentOutput("outColor");
    vShader.free();
    fShader.free();

    vShader.initFromFile(VERTEX_SHADER, "shaders/maskedTexture.vert");
    if (!vShader.isCompiled()) {
        cout << "Vertex Shader Error" << endl;
        cout << "" << vShader.log() << endl << endl;
    }
    fShader.initFromFile(FRAGMENT_SHADER, "shaders/maskedTexture.frag");
    if (!fShader.isCompiled()) {
        cout << "Fragment Shader Error" << endl;
        cout << "" << fShader.log() << endl << endl;
    }
    _maskedTexProgram.init();
    _maskedTexProgram.addShader(vShader);
    _maskedTexProgram.addShader(fShader);
    _maskedTexProgram.link();
    if (!_maskedTexProgram.isLinked()) {
        cout << "Shader Linking Error" << endl;
        cout << "" << _maskedTexProgram.log() << endl << endl;
    }
    _maskedTexProgram.bindFragmentOutput("outColor");
    vShader.free();
    fShader.free();

    _projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);
}

ShaderProgram &ShaderManager::getShaderProgram() {
    return _simpleTexProgram;
}

ShaderProgram &ShaderManager::getMaskedShaderProgram() {
    return _maskedTexProgram;
}


void ShaderManager::useMaskedShaderProgram() {
    _maskedTexProgram.use();
    _maskedTexProgram.setUniformMatrix4f("projection", _projection);
    _maskedTexProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
    _modelView = glm::mat4(1.0f);
    _maskedTexProgram.setUniformMatrix4f("modelview", _modelView);
}

void ShaderManager::useShaderProgram() {
    _simpleTexProgram.use();
    _simpleTexProgram.setUniformMatrix4f("projection", _projection);
    _simpleTexProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
    _modelView = glm::mat4(1.0f);
    _simpleTexProgram.setUniformMatrix4f("modelview", _modelView);
}

glm::mat4 ShaderManager::getProjectionMatrix() {
    return _projection;
}


