#ifndef _KEYBOARDMANAGER_INCLUDE
#define _KEYBOARDMANAGER_INCLUDE

struct IKeyboardManager {

public:

    virtual ~IKeyboardManager() = default;

    virtual void keyPressed(int key) = 0;

    virtual void keyReleased(int key) = 0;

    virtual void specialKeyPressed(int key) = 0;

    virtual void specialKeyReleased(int key) = 0;

};

#endif // _KEYBOARDMANAGER_INCLUDE