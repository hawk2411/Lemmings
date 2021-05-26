#ifndef _EXPLODER_INCLUDE
#define _EXPLODER_INCLUDE


#include "Job.h"


class Exploder : public Job {
public:
    Exploder(SoundManager *soundManager);

    void initAnims(ShaderProgram &shaderProgram);

    void updateStateMachine(int deltaTime, Level *levelAttributes, IMaskManager *mask);

    void setWalkingRight(bool value);

    string getName() const override { return "BOMBER"; }

private:
    enum ExploderState {
        EXPLODER_STATE,
        BURNING_DEATH_STATE
    };


private:
    ExploderState _state;

    void explode(IMaskManager *mask);
};


#endif // _EXPLODER_INCLUDE



