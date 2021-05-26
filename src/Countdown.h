#ifndef _COUNTDOWN_INCLUDE
#define _COUNTDOWN_INCLUDE

#include <glm/glm.hpp>
#include "Sprite.h"
#include "ShaderManager.h"

class Countdown {

public:

    Countdown(ShaderManager *shaderManager);

    void render(const glm::vec2 &cameraPos);

    void setPosition(glm::vec2 position);

    void update(int deltaTime);

    bool isOver() const;

    void start(int goalTime);

    void reset();

    bool isStarted() const;

private:
    std::unique_ptr<Sprite> _countNum;
    ShaderManager* _shaderManager;
    int _goalTime;
    bool _over;
    bool _isStarted;

};

#endif // _COUNTDOWN_INCLUDE


