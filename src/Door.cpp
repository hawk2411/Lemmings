#include "Door.h"

Door::Door(ShaderManager *shaderManager) : _shaderManager(shaderManager), _escapeOffset(13,16) {}

void Door::update(int deltaTime) {
    _doorSprite->update(deltaTime);
}

void Door::render(glm::vec2 cameraPos) {
    glm::vec2 oldPosition = _doorSprite->getPosition();
    _doorSprite->setPosition(_doorSprite->getPosition() - cameraPos);
    _doorSprite->render();
    _doorSprite->setPosition(oldPosition);
}


void Door::setPosition(glm::vec2 position) {
    _doorSprite->setPosition(position);
}

glm::vec2 Door::getPosition() const {
    return _doorSprite->getPosition();
}

glm::vec2 Door::getEscapePosition() const {
    return _doorSprite->getPosition() + _escapeOffset;
}
