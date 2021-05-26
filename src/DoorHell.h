#ifndef _DOORHELL_INCLUDE
#define _DOORHELL_INCLUDE

#include "Door.h"


class DoorHell : public Door {

public:
    explicit DoorHell(ShaderManager *shaderManager);

    void init() override;
};


#endif // _DOORHELL_INCLUDE

