#ifndef _CURSOR_INCLUDE
#define _CURSOR_INCLUDE


#include "Sprite.h"

class Cursor {
public:
    void init();

    void render();

    void setPosition(glm::vec2 position);

    void setScrollLeftCursor();

    void setScrollRightCursor();

    void setFocusCursor();

    void setCrossCursor();

private:
    glm::vec2 position = {};
    std::unique_ptr<Sprite> cursorSprite = nullptr;
};


#endif // _CURSOR_INCLUDE



