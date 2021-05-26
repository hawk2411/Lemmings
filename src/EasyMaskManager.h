#ifndef _EASYMASKMANAGER_INCLUDE
#define _EASYMASKMANAGER_INCLUDE

#include "IMaskManager.h"

class EasyMaskManager : public IMaskManager {
public:
    explicit EasyMaskManager(Level* level): IMaskManager(level){}

    void init() override;

    void update(int time) override;

    void eraseMask(int x, int y, int time) override;

    void applyMask(int x, int y) override;

    void eraseSpecialMask(int x, int y) override;

    void applySpecialMask(int x, int y) override;

    char getPixel(int x, int y) override;

};


#endif // _EASYMASKMANAGER_INCLUDE



