#ifndef _DOOREGYPT_INCLUDE
#define _DOOREGYPT_INCLUDE

#include "Door.h"


class DoorEgypt : public Door {

public:
    explicit DoorEgypt(ShaderManager *shaderManager);

    void init() override;
};


#endif // _DOOREGYPT_INCLUDE

