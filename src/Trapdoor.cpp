#include "Trapdoor.h"

Trapdoor::Trapdoor(ShaderManager *shaderManager) : _shaderManager(shaderManager){

}

void Trapdoor::update(int deltaTime) {
    if (_trapdoorSprite->isInLastFrame()) {
        _trapdoorSprite->setAnimationSpeed(0, 0);
        opened = true;
    }
    _trapdoorSprite->update(deltaTime);
}

void Trapdoor::render(glm::vec2 cameraPos) {
    glm::vec2 oldPosition = _trapdoorSprite->getPosition();
    _trapdoorSprite->setPosition(oldPosition - cameraPos);
    _trapdoorSprite->render();
    _trapdoorSprite->setPosition(oldPosition);
}

bool Trapdoor::isOpened() const {
    return opened;
}

void Trapdoor::setPosition(glm::vec2 position) {
    _trapdoorSprite->setPosition(position);
}


glm::vec2 Trapdoor::getPosition() {
    return _trapdoorSprite->getPosition();
}

glm::vec2 Trapdoor::getEnterPosition() {
    return _trapdoorSprite->getPosition() + _enterOffset;
}

