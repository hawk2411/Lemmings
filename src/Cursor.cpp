#include "Cursor.h"
#include "Game.h"
#include "ShaderManager.h"

enum CursorStates {
    CROSS,
    FOCUS,
    LEFT,
    RIGHT
};

Cursor::Cursor(ShaderManager* shaderManager) {

    _cursorSprite = Sprite::createSprite(glm::ivec2(12, 12), glm::vec2(29. / 32, 29. / 128),
                                         &shaderManager->getShaderProgram(),
                                         &Game::spriteSheets().cursorSprites);

}

void Cursor::init() {
    SDL_WarpMouseGlobal(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    _cursorSprite->setNumberAnimations(4);

    _cursorSprite->setAnimationSpeed(CROSS, 12);
    _cursorSprite->addKeyframe(CROSS, glm::vec2(0, 87. / 128));

    _cursorSprite->setAnimationSpeed(FOCUS, 12);
    _cursorSprite->addKeyframe(FOCUS, glm::vec2(0, 58. / 128));

    _cursorSprite->setAnimationSpeed(LEFT, 12);
    _cursorSprite->addKeyframe(LEFT, glm::vec2(0, 0));

    _cursorSprite->setAnimationSpeed(RIGHT, 12);
    _cursorSprite->addKeyframe(RIGHT, glm::vec2(0, 29. / 128));

    _cursorSprite->changeAnimation(CROSS);
}

void Cursor::render() {
    _cursorSprite->render();
}

void Cursor::setScrollLeftCursor() {
    _cursorSprite->changeAnimation(LEFT);
}

void Cursor::setScrollRightCursor() {
    _cursorSprite->changeAnimation(RIGHT);
}

void Cursor::setFocusCursor() {
    _cursorSprite->changeAnimation(FOCUS);
}

void Cursor::setCrossCursor() {
    _cursorSprite->changeAnimation(CROSS);
}

void Cursor::setPosition(glm::vec2 newPosition) {
    _cursorSprite->setPosition(newPosition);
}

