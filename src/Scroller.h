#ifndef _SCROLLER_INCLUDE
#define _SCROLLER_INCLUDE


#include <glm/vec2.hpp>

class Scroller {

public:
    explicit Scroller(bool scrolled);

    void scrollLeft(glm::vec2 cameraPos, int levelSize);

    void scrollRight(glm::vec2 cameraPos, int levelSize);

    bool isScrolled() const;

    void setScroll(bool isScroll);

private:
    void scroll(int scrollDisplacement, glm::vec2 cameraPos, int levelSize);

    bool _scrolled;
};

#endif // _SCROLLER_INCLUDE


