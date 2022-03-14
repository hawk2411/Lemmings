#include "EasyMaskManager.h"

void EasyMaskManager::init() {

}

void EasyMaskManager::update(int time) {

}

void EasyMaskManager::eraseMask(int x, int y, int time) {
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

