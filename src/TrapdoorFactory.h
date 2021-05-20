#ifndef _TRAPDOORFACTORY_INCLUDE
#define _TRAPDOORFACTORY_INCLUDE

#include "Sprite.h"
#include "Trapdoor.h"

class TrapdoorFactory {

public:
    static Trapdoor *createTrapdoor(const string& type);

};


#endif // _TRAPDOORFACTORY_INCLUDE

