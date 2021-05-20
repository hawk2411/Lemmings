#include "EasyMaskManager.h"
#include "Level.h"

void EasyMaskManager::init() {

}

void EasyMaskManager::update() {

}

void EasyMaskManager::eraseMask(int x, int y) {
    if (getPixel(x, y) != 200) {
        _level->maskedMap.setPixel(x, y, 0);
    }
}

void EasyMaskManager::applyMask(int x, int y) {
    _level->maskedMap.setPixel(x, y, 255);

}

void EasyMaskManager::eraseSpecialMask(int x, int y) {
    _level->maskedMap.setPixel(x, y, 0);

}

void EasyMaskManager::applySpecialMask(int x, int y) {
    _level->maskedMap.setPixel(x, y, 200);
}

char EasyMaskManager::getPixel(int x, int y) {
    return _level->maskedMap.pixel(x, y);
}

