#ifndef _COUNTDOWN_INCLUDE
#define _COUNTDOWN_INCLUDE

#include <glm/glm.hpp>
#include "Sprite.h"

class Countdown {

public:

    Countdown();

    void render();

    void setPosition(glm::vec2 position);

    void update(int deltaTime);

    bool isOver() const;

    void start(int goalTime);

    void reset();

    bool isStarted() const;

private:
    std::unique_ptr<Sprite> _countNum;
    int _goalTime;
    bool _over;
    bool _isStarted;

};

#endif // _COUNTDOWN_INCLUDE


