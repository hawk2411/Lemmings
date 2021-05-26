#ifndef _DOORMAYA_INCLUDE
#define _DOORMAYA_INCLUDE

#include "Door.h"


class DoorMaya : public Door {

public:
    explicit DoorMaya(ShaderManager *shaderManager);

    void init() override;
};


#endif // _DOORMAYA_INCLUDE

