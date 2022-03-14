#ifndef _HARDMASKMANAGER_INCLUDE
#define _HARDMASKMANAGER_INCLUDE

#include <vector>
#include "IMaskManager.h"
#include "EasyMaskManager.h"

class HardMaskManager : public EasyMaskManager  {
public:
    explicit HardMaskManager(Level* level) : EasyMaskManager(level){}

    void init() override;

    void update(int time) override;

    void eraseMask(int x, int y, int time) override;

    void applyMask(int x, int y) override;

private:
    void regenerateMask(int x, int y);

    std::vector<std::vector<int>> _timeWhenDisappear;
    std::vector<std::vector<int>> _timeToAppear;
};


#endif // _HARDMASKMANAGER_INCLUDE


