#ifndef _DOORFACTORY_INCLUDE
#define _DOORFACTORY_INCLUDE

#include "Sprite.h"
#include "Door.h"

class DoorFactory {

public:

    static DoorFactory &instance() {
        static DoorFactory instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    };

    static Door *createDoor(const string &type);

};


#endif // _DOORFACTORY_INCLUDE

