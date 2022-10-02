#include <SOIL/src/SOIL.h>
#include <memory>
#include "Texture.h"


using namespace std;


Texture::Texture() :
        _wrapS(GL_REPEAT),
        _wrapT(GL_REPEAT),
        _minFilter(GL_LINEAR_MIPMAP_LINEAR),
        _magFilter(GL_LINEAR_MIPMAP_LINEAR),
        _widthTex(0),
        _heightTex(0),
        _texId(0) {}

Texture::~Texture() {
    glDeleteBuffers(1, &_texId);
}

bool Texture::loadFromFile(const string &filename, PixelFormat format) {

    std::unique_ptr<unsigned char, decltype(&SOIL_free_image_data)> image(nullptr, SOIL_free_image_data);

    switch (format) {
        case PixelFormat::TEXTURE_PIXEL_FORMAT_RGB:
            image = std::unique_ptr<unsigned char, decltype(&SOIL_free_image_data)>(SOIL_load_image(filename.c_str(), &_widthTex, &_heightTex, nullptr, SOIL_LOAD_RGB),
                                                    SOIL_free_image_data);
            break;
        case PixelFormat::TEXTURE_PIXEL_FORMAT_RGBA:
            image = std::unique_ptr<unsigned char, decltype(&SOIL_free_image_data)>(SOIL_load_image(filename.c_str(), &_widthTex, &_heightTex, nullptr, SOIL_LOAD_RGBA),
                                                                                    SOIL_free_image_data);
            break;
        case PixelFormat::TEXTURE_PIXEL_FORMAT_L:
            break;
    }
    if (!image) {
        return false;
    }

    glGenTextures(1, &_texId);
    glBindTexture(GL_TEXTURE_2D, _texId);
    switch (format) {
        case PixelFormat::TEXTURE_PIXEL_FORMAT_RGB:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _widthTex, _heightTex, 0, GL_RGB, GL_UNSIGNED_BYTE, image.get());
            break;
        case PixelFormat::TEXTURE_PIXEL_FORMAT_RGBA:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _widthTex, _heightTex, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.get());
            break;
        case PixelFormat::TEXTURE_PIXEL_FORMAT_L:
            break;
    }
    glGenerateMipmap(GL_TEXTURE_2D);

    return true;
}

void Texture::loadFromGlyphBuffer(unsigned char *buffer, int width, int height) {
    glGenTextures(1, &_texId);
    glBindTexture(GL_TEXTURE_2D, _texId);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, buffer);
    glGenerateMipmap(GL_TEXTURE_2D);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}

void Texture::createEmptyTexture(int width, int height) {
    glGenTextures(1, &_texId);
    glBindTexture(GL_TEXTURE_2D, _texId);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, nullptr);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}

void Texture::loadSubtextureFromGlyphBuffer(unsigned char *buffer, int x, int y, int width, int height) const {
    glBindTexture(GL_TEXTURE_2D, _texId);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, GL_RED, GL_UNSIGNED_BYTE, buffer);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}

void Texture::generateMipmap() const {
    glBindTexture(GL_TEXTURE_2D, _texId);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenerateMipmap(GL_TEXTURE_2D);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}

void Texture::setWrapS(GLint value) {
    _wrapS = value;
}

void Texture::setWrapT(GLint value) {
    _wrapT = value;
}

void Texture::setMinFilter(GLint value) {
    _minFilter = value;
}

void Texture::setMagFilter(GLint value) {
    _magFilter = value;
}

void Texture::use() const {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _texId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _magFilter);
}

GLuint Texture::getId() const {
    return _texId;
}


