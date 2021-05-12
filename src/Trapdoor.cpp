#include <iostream>
#include "Trapdoor.h"
#include "Game.h"


void Trapdoor::update(int deltaTime) {
    if (trapdoorSprite->isInLastFrame()) {
        trapdoorSprite->setAnimationSpeed(0, 0);
        opened = true;
    }
    trapdoorSprite->update(deltaTime);
}

void Trapdoor::render() {
    glm::vec2 oldPosition = trapdoorSprite->getPosition();
    trapdoorSprite->setPosition(oldPosition - Level::currentLevel().getLevelAttributes()->cameraPos);
    trapdoorSprite->render();
    trapdoorSprite->setPosition(oldPosition);
}

bool Trapdoor::isOpened() {
    return opened;
}

void Trapdoor::setPosition(glm::vec2 position) {
    trapdoorSprite->setPosition(position);
}


glm::vec2 Trapdoor::getPosition() {
    return trapdoorSprite->getPosition();
}

glm::vec2 Trapdoor::getEnterPosition() {
    return trapdoorSprite->getPosition() + enterOffset;
}