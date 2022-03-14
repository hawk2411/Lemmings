#ifndef _DOOR_INCLUDE
#define _DOOR_INCLUDE

#include "Sprite.h"
#include "ShaderManager.h"


class Door {

public:
    explicit Door(ShaderManager *shaderManager);

    virtual void init() = 0;

    void update(int deltaTime);

    void render(glm::vec2 cameraPos);

    void setPosition(glm::vec2 position);

    glm::vec2 getPosition() const;

    glm::vec2 getEscapePosition() const;

protected:
    std::unique_ptr<Sprite> _doorSprite;
    glm::vec2 _escapeOffset;
    ShaderManager * _shaderManager;
};


#endif // _DOOR_INCLUDE

