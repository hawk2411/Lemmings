#ifndef _TRAPDOORHELL_INCLUDE
#define _TRAPDOORHELL_INCLUDE

#include "Trapdoor.h"
#include "Sprite.h"


class TrapdoorHell : public Trapdoor {

public:
    explicit TrapdoorHell(ShaderManager *shaderManager);

    void init() override;

};


#endif // _TRAPDOORHELL_INCLUDE

