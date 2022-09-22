#include "common_defs.h"
#include "Scroller.h"


#define SCROLL_BASE_DISPLACEMENT 5

Scroller::Scroller(bool scrolled) : _scrolled(scrolled) {}

void Scroller::scrollLeft(glm::vec2 &cameraPos, int levelSize ) {
    int scrollDisplacement = -SCROLL_BASE_DISPLACEMENT;
    scroll(scrollDisplacement, cameraPos, levelSize);

}

void Scroller::scrollRight(glm::vec2 &cameraPos, int levelSize) {
    int scrollDisplacement = SCROLL_BASE_DISPLACEMENT;
    scroll(scrollDisplacement, cameraPos, levelSize);
}

bool Scroller::isScrolled() const {
    return _scrolled;
}

void Scroller::setScroll(bool isScroll) {
    _scrolled = isScroll;
}

void Scroller::scroll(int scrollDisplacement, glm::vec2 &cameraPos, int levelSize) {
    int maxCameraPosX = levelSize - LEVEL_WIDTH;

    struct scroll_result_t {
        bool scrolled = false;
        glm::vec2 camera_pos = {0.0, 0.0};
    };
    scroll_result_t scrollResult;

    if (static_cast<int>(cameraPos.x) + scrollDisplacement >= 0 && static_cast<int>(cameraPos.x) + scrollDisplacement <= maxCameraPosX) {
        cameraPos += glm::vec2(scrollDisplacement, 0);
        _scrolled = true;
    }

}


