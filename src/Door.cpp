#include <iostream>
#include "Door.h"
#include "Game.h"


void Door::update(int deltaTime) {
    doorSprite->update(deltaTime);
}

void Door::render() {
    glm::vec2 oldPosition = doorSprite->getPosition();
    doorSprite->setPosition(doorSprite->getPosition() - Level::currentLevel().getLevelAttributes()->cameraPos);
    doorSprite->render();
    doorSprite->setPosition(oldPosition);
}

void Door::setPosition(glm::vec2 position) {
    doorSprite->setPosition(position);
}


glm::vec2 Door::getPosition() const {
    return doorSprite->getPosition();
}

glm::vec2 Door::getEscapePosition() const {
    return doorSprite->getPosition() + escapeOffset;
}