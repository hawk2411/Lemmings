#ifndef _ESCAPER_INCLUDE
#define _ESCAPER_INCLUDE


#include "Job.h"
#include "MusicFabric.hpp"


class Escaper : public Job {
public:
    Escaper();

    void initAnims(ShaderProgram &shaderProgram);

    void updateStateMachine(int deltaTime, Level *levelAttributes, IMaskManager *mask);

    void setWalkingRight(bool value);

    string getName() const override {return "ESCAPER";}

private:
    enum EscaperState {
        ESCAPING_STATE
    };


private:
    EscaperState state;
    sound_ptr_t escapeEffect_;
};


#endif // _ESCAPER_INCLUDE


