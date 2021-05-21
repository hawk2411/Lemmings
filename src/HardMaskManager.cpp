#include "HardMaskManager.h"
#include "Level.h"
#include "LevelRunner.h"

#define SEC_TO_REAPPEAR 10

void HardMaskManager::init() {
    int levelHeight = _level->levelSize.y;
    int levelWidth = _level->levelSize.x;
    timeWhenDisappear = std::vector<std::vector<int>>(levelWidth, std::vector<int>(levelHeight, -1));
    timeToAppear = std::vector<std::vector<int>>(levelWidth, std::vector<int>(levelHeight, -1));

}

void HardMaskManager::update(int time) {
    int currentTime = time * 10;

    int levelHeight = _level->levelSize.y;
    int levelWidth = _level->levelSize.x;

    for (int i = 0; i < levelWidth; ++i) {
        for (int j = 0; j < levelHeight; ++j) {
            int currentTimeWhenDisappear = timeWhenDisappear[i][j];
            int currentTimeToAppear = timeToAppear[i][j];

            if (currentTimeWhenDisappear != -1 && currentTime >= currentTimeToAppear) {
                regenerateMask(i, j);
            }
        }
    }
}

void HardMaskManager::eraseMask(int x, int y, int time) {
    if (getPixel(x, y) != 200) {
        int currentTime = time * 10;
        timeWhenDisappear[x][y] = currentTime;
        timeToAppear[x][y] = currentTime + rand() % 6 + (SEC_TO_REAPPEAR + rand() % 3) * 10;

        _level->maskedMap.setPixel(x, y, 0);
    }
}

void HardMaskManager::applyMask(int x, int y) {
    timeWhenDisappear[x][y] = -1;
    timeToAppear[x][y] = -1;

    _level->maskedMap.setPixel(x, y, 255);

}

void HardMaskManager::eraseSpecialMask(int x, int y) {
    _level->maskedMap.setPixel(x, y, 0);

}

void HardMaskManager::applySpecialMask(int x, int y) {
    _level->maskedMap.setPixel(x, y, 200);
}

char HardMaskManager::getPixel(int x, int y) {
    return _level->maskedMap.pixel(x, y);
}

void HardMaskManager::regenerateMask(int x, int y) {
    applyMask(x, y);
}





