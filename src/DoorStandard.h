#ifndef _DOORSTANDARD_INCLUDE
#define _DOORSTANDARD_INCLUDE

#include "Door.h"


class DoorStandard : public Door {

public:
    explicit DoorStandard(ShaderManager *shaderManager);

    void init() override;
};


#endif // _DOORSTANDARD_INCLUDE

