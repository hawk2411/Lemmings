#ifndef _HARDMASKMANAGER_INCLUDE
#define _HARDMASKMANAGER_INCLUDE

#include "IMaskManager.h"

#include <vector>

class HardMaskManager : public IMaskManager {
public:
    explicit HardMaskManager(Level* level) : IMaskManager(level){}
    void init() override;

    void update() override;

    void eraseMask(int x, int y) override;

    void applyMask(int x, int y) override;

    void eraseSpecialMask(int x, int y) override;

    void applySpecialMask(int x, int y) override;

    char getPixel(int x, int y) override;

private:
    void regenerateMask(int x, int y);

    std::vector<std::vector<int>> timeWhenDisappear;
    std::vector<std::vector<int>> timeToAppear;
};


#endif // _HARDMASKMANAGER_INCLUDE


