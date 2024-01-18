#ifndef _TRAPDOOR_INCLUDE
#define _TRAPDOOR_INCLUDE

#include "Sprite.h"
#include "ShaderManager.h"

class Trapdoor {

public:
    explicit Trapdoor(ShaderManager* shaderManager);
    virtual ~Trapdoor() = default;

    virtual void init() = 0;

    void update(int deltaTime);

    void render(glm::vec2 cameraPos);

    void setPosition(glm::vec2 position);

    glm::vec2 getPosition();

    glm::vec2 getEnterPosition();

    bool isOpened() const;

protected:
    std::unique_ptr<Sprite> _trapdoorSprite;
    glm::vec2 _enterOffset{};
    bool opened = false;
    ShaderManager* _shaderManager;
};


#endif // _TRAPDOOR_INCLUDE

