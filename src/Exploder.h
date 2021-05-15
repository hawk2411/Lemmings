#ifndef _EXPLODER_INCLUDE
#define _EXPLODER_INCLUDE


#include "Job.h"


class Exploder : public Job {
public:
    Exploder(Jobs jobs);

    void initAnims(ShaderProgram &shaderProgram);

    void updateStateMachine(int deltaTime);

    void setWalkingRight(bool value);

    string getName() const override { return "BOMBER"; }

private:
    enum ExploderState {
        EXPLODER_STATE,
        BURNING_DEATH_STATE
    };


private:
    ExploderState state;

    void explode();
};


#endif // _EXPLODER_INCLUDE



