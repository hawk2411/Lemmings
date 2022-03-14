#ifndef _ESCAPER_INCLUDE
#define _ESCAPER_INCLUDE


#include "Job.h"
#include "MusicFabric.hpp"


class Escaper : public Job {
public:
    Escaper();

    void initAnims(ShaderProgram &shaderProgram) override;

    void updateStateMachine(int deltaTime, Level *levelAttributes, IMaskManager *mask) override;

    void setWalkingRight(bool value) override;

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


