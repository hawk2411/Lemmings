#ifndef _MOUSEMANAGER_INCLUDE
#define _MOUSEMANAGER_INCLUDE


class MouseManager {

public:


    virtual void mouseMove(int x, int y) = 0;

    virtual void mousePress(int button) = 0;

    virtual void mouseRelease(int button) = 0;

};

#endif // _MOUSEMANAGER_INCLUDE

