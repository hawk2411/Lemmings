
#ifndef _TRAPDOORSTANDARD_INCLUDE
#define _TRAPDOORSTANDARD_INCLUDE

#include "Trapdoor.h"
#include "Sprite.h"


class TrapdoorStandard : public Trapdoor {

public:
    explicit TrapdoorStandard(ShaderManager* shaderManager);
    void init() override;

};


#endif //_TRAPDOORSTANDARD_INCLUDE

