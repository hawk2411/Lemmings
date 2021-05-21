#include "Scroller.h"
#include "Level.h"

#define SCROLL_BASE_DISPLACEMENT 5

void Scroller::scrollLeft(glm::vec2 cameraPos, int levelSize ) {
    int scrollDisplacement = -SCROLL_BASE_DISPLACEMENT;
    scroll(scrollDisplacement, cameraPos, levelSize);

}

void Scroller::scrollRight(glm::vec2 cameraPos, int levelSize) {
    int scrollDisplacement = SCROLL_BASE_DISPLACEMENT;
    scroll(scrollDisplacement, cameraPos, levelSize);
}

bool Scroller::isScrolled() const {
    return scrolled;
}

void Scroller::setScroll(bool isScroll) {
    scrolled = isScroll;
}

void Scroller::scroll(int scrollDisplacement, glm::vec2 cameraPos, int levelSize) {
    int maxCameraPosX = levelSize - LEVEL_WIDTH;

    if (static_cast<int>(cameraPos.x) + scrollDisplacement >= 0 && static_cast<int>(cameraPos.x) + scrollDisplacement <= maxCameraPosX) {
        cameraPos += glm::vec2(scrollDisplacement, 0);
        scrolled = true;
    }
}