#ifndef _EASYMASKMANAGER_INCLUDE
#define _EASYMASKMANAGER_INCLUDE

#include "IMaskManager.h"

class EasyMaskManager : public IMaskManager {
public:

    void init() override;

    void update() override;

    void eraseMask(int x, int y) override;

    void applyMask(int x, int y) override;

    void eraseSpecialMask(int x, int y) override;

    void applySpecialMask(int x, int y) override;

    char getPixel(int x, int y) override;

};


#endif // _EASYMASKMANAGER_INCLUDE



