#ifndef _NUMDISPLAY_INCLUDE
#define _NUMDISPLAY_INCLUDE

#include "Texture.h"
#include "Sprite.h"
#include "ShaderManager.h"

// Lemming is basically a Sprite that represents one lemming. As such it has
// all properties it needs to track its movement and collisions.


class NumDisplay {

public:
    void init(ShaderManager *shaderManager);

    void displayNum(int num);

    void render();

    virtual void setPosition(glm::vec2 position) = 0;

protected:
    virtual void initAux(ShaderManager *shaderManager) = 0;

    virtual void displayNumAux(int firstDigit, int secondDigit) = 0;

protected:
    glm::vec2 _position;
    std::unique_ptr<Sprite> _leftNum;
    std::unique_ptr<Sprite> _rightNum;

};

#endif // _NUMDISPLAY_INCLUDE


