#ifndef _WALKER_INCLUDE
#define _WALKER_INCLUDE


#include "Job.h"


// Lemming is basically a Sprite that represents one lemming. As such it has
// all properties it needs to track its movement and collisions.


class Walker : public Job {


public:
    Walker();
    void initAnims(ShaderProgram &shaderProgram) override;

    void updateStateMachine(int deltaTime, Level *levelAttributes, IMaskManager *mask) override;

    void setWalkingRight(bool value) override;

    string getName() const override {return "WALKER"; }


private:
    enum WalkerState {
        WALKING_LEFT_STATE, WALKING_RIGHT_STATE
    };

private:
    WalkerState _state;
};

#endif // _WALKER_INCLUDE


