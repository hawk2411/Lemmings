#include <SOIL/SOIL.h>
#include "VariableTexture.h"


using namespace std;


VariableTexture::VariableTexture() :
        _wrapS(GL_REPEAT),
        _wrapT(GL_REPEAT),
        _minFilter(GL_LINEAR_MIPMAP_LINEAR),
        _magFilter(GL_LINEAR_MIPMAP_LINEAR),
        _image(nullptr),
        _widthTex(0),
        _heightTex(0),
        _texId(0),
        _format{} {}

VariableTexture::~VariableTexture() {
    if (_image)
        SOIL_free_image_data(_image);
}


bool VariableTexture::loadFromFile(const string &filename, PixelFormat imageFormat) {
    int channels = 0;
    _format = imageFormat;
    switch (_format) {
        case TEXTURE_PIXEL_FORMAT_RGB:
            _image = SOIL_load_image(filename.c_str(), &_widthTex, &_heightTex, &channels, SOIL_LOAD_RGB);
            break;
        case TEXTURE_PIXEL_FORMAT_RGBA:
            _image = SOIL_load_image(filename.c_str(), &_widthTex, &_heightTex, &channels, SOIL_LOAD_RGBA);
            break;
        case TEXTURE_PIXEL_FORMAT_L:
            _image = SOIL_load_image(filename.c_str(), &_widthTex, &_heightTex, &channels, SOIL_LOAD_L);
            break;
    }
    if (!_image)
        return false;
    glGenTextures(1, &_texId);
    glBindTexture(GL_TEXTURE_2D, _texId);
    switch (_format) {
        case TEXTURE_PIXEL_FORMAT_RGB:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _widthTex, _heightTex, 0, GL_RGB, GL_UNSIGNED_BYTE, _image);
            break;
        case TEXTURE_PIXEL_FORMAT_RGBA:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _widthTex, _heightTex, 0, GL_RGBA, GL_UNSIGNED_BYTE, _image);
            break;
        case TEXTURE_PIXEL_FORMAT_L:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, _widthTex, _heightTex, 0, GL_RED, GL_UNSIGNED_BYTE, _image);
            break;
    }
    glGenerateMipmap(GL_TEXTURE_2D);

    return true;
}

void VariableTexture::loadFromGlyphBuffer(unsigned char *buffer, int width, int height) {
    glGenTextures(1, &_texId);
    glBindTexture(GL_TEXTURE_2D, _texId);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, buffer);
    glGenerateMipmap(GL_TEXTURE_2D);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}

void VariableTexture::createEmptyTexture(int width, int height) {
    glGenTextures(1, &_texId);
    glBindTexture(GL_TEXTURE_2D, _texId);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}

void VariableTexture::loadSubtextureFromGlyphBuffer(unsigned char *buffer, int x, int y, int width, int height) {
    glBindTexture(GL_TEXTURE_2D, _texId);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, GL_RED, GL_UNSIGNED_BYTE, buffer);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}

void VariableTexture::generateMipmap() {
    glBindTexture(GL_TEXTURE_2D, _texId);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenerateMipmap(GL_TEXTURE_2D);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}

void VariableTexture::setWrapS(GLint value) {
    _wrapS = value;
}

void VariableTexture::setWrapT(GLint value) {
    _wrapT = value;
}

void VariableTexture::setMinFilter(GLint value) {
    _minFilter = value;
}

void VariableTexture::setMagFilter(GLint value) {
    _magFilter = value;
}

void VariableTexture::use() const {
    if (!_image)
        return;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _texId);
    switch (_format) {
        case TEXTURE_PIXEL_FORMAT_RGB:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _widthTex, _heightTex, 0, GL_RGB, GL_UNSIGNED_BYTE, _image);
            break;
        case TEXTURE_PIXEL_FORMAT_RGBA:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _widthTex, _heightTex, 0, GL_RGBA, GL_UNSIGNED_BYTE, _image);
            break;
        case TEXTURE_PIXEL_FORMAT_L:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, _widthTex, _heightTex, 0, GL_RED, GL_UNSIGNED_BYTE, _image);
            break;
    }
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _magFilter);
}

unsigned char VariableTexture::pixel(unsigned int x, unsigned int y) const {
    switch (_format) {
        case TEXTURE_PIXEL_FORMAT_RGB :
            return _image[3 * (y * _widthTex + x)];
        case TEXTURE_PIXEL_FORMAT_RGBA:
            return _image[4 * (y * _widthTex + x)];
        default:
            return _image[y * _widthTex + x];
    }
}

void VariableTexture::setPixel(unsigned int x, unsigned int y, unsigned char value) {
    if (_format == TEXTURE_PIXEL_FORMAT_L) {
        _image[y * _widthTex + x] = value;
    }
}

void VariableTexture::setPixel(unsigned int x, unsigned int y, const glm::ivec3 &value) {
    if (_format == TEXTURE_PIXEL_FORMAT_RGB) {
        _image[3 * (y * _widthTex + x)] = value.r;
        _image[3 * (y * _widthTex + x) + 1] = value.g;
        _image[3 * (y * _widthTex + x) + 2] = value.b;
    }
}

void VariableTexture::setPixel(unsigned int x, unsigned int y, const glm::ivec4 &value) {
    if (_format == TEXTURE_PIXEL_FORMAT_RGBA) {
        _image[4 * (y * _widthTex + x)] = value.r;
        _image[4 * (y * _widthTex + x) + 1] = value.g;
        _image[4 * (y * _widthTex + x) + 2] = value.b;
        _image[4 * (y * _widthTex + x) + 3] = value.a;
    }
}

void VariableTexture::saveBMP(const string &filename) {
    if (_format == TEXTURE_PIXEL_FORMAT_RGB)
        SOIL_save_image(filename.c_str(), SOIL_SAVE_TYPE_BMP, _widthTex, _heightTex, 3, _image);
    else
        SOIL_save_image(filename.c_str(), SOIL_SAVE_TYPE_BMP, _widthTex, _heightTex, 4, _image);
}







