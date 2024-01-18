#ifndef _MASKMANAGER_INCLUDE
#define _MASKMANAGER_INCLUDE

#include "Level.h"

class IMaskManager {
public:
    explicit IMaskManager(Level *level) : _level(level) {}

    virtual ~IMaskManager() = default;

    virtual void init() = 0;

    virtual void update(int time) = 0;

    virtual void eraseMask(int x, int y, int time) = 0;

    virtual void applyMask(int x, int y) = 0;

    virtual void eraseSpecialMask(int x, int y) = 0;

    virtual void applySpecialMask(int x, int y) = 0;

    virtual unsigned char getPixel(int x, int y)const { return _level->maskedMap.pixel(x, y);}

    virtual bool isPositionABorder(int x, int y)const { return _level->maskedMap.pixel(x, y) == IMaskManager::MASK_COLOR_WHITE;}

    virtual void changeLevel(Level *level) {_level = level;};

protected:
    Level *_level;
    static const unsigned char MASK_COLOR_WHITE = 255;
};


#endif // _MASKMANAGER_INCLUDE



