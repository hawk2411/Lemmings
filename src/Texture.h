#ifndef _TEXTURE_INCLUDE
#define _TEXTURE_INCLUDE


#include <string>
#include <GL/glew.h>
#include "common_defs.h"


using namespace std;


// The _texture class loads images an passes them to OpenGL
// storing the returned id so that it may be applied to any drawn primitives


class Texture {

public:
    Texture();
    ~Texture();
    bool loadFromFile(const string &filename, PixelFormat format);

    void loadFromGlyphBuffer(unsigned char *buffer, int width, int height);

    void createEmptyTexture(int width, int height);

    void loadSubtextureFromGlyphBuffer(unsigned char *buffer, int x, int y, int width, int height) const;

    void generateMipmap() const;

    void setWrapS(GLint value);

    void setWrapT(GLint value);

    void setMinFilter(GLint value);

    void setMagFilter(GLint value);

    void use() const;

    int width() const { return _widthTex; }

    int height() const { return _heightTex; }

    GLuint getId() const;

private:
    int _widthTex, _heightTex;
    GLuint _texId;
    GLint _wrapS, _wrapT, _minFilter, _magFilter;

};


#endif // _TEXTURE_INCLUDE

