#ifndef _BLOCKER_INCLUDE
#define _BLOCKER_INCLUDE


#include "Job.h"


// Lemming is basically a Sprite that represents one lemming. As such it has
// all properties it needs to track its movement and collisions.


class Blocker : public Job {
public:
    void initAnims(ShaderProgram &shaderProgram) override;

    void updateStateMachine(int deltaTime) override;

    void setWalkingRight(bool value) override;

    string getName() const override{
        return "BLOCKER";
    }

private:
    enum BlockerState {
        BLOCKING_STATE
    };


private:
    BlockerState state;
};


#endif // _BLOCKER_INCLUDE



