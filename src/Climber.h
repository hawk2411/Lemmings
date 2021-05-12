#ifndef _CLIMBER_INCLUDE
#define _CLIMBER_INCLUDE


#include "Job.h"


class Climber : public Job {


public:
    void initAnims(ShaderProgram &shaderProgram) override;

    void updateStateMachine(int deltaTime) override;

    void setWalkingRight(bool value) override;

    string getName() const override { return "CLIMBER"; }


private:
    enum CLimberState {
        WALKING_LEFT_STATE,
        WALKING_RIGHT_STATE,
        CLIMBING_LEFT_STATE,
        CLIMBING_RIGHT_STATE,
        LEDGING_LEFT_STATE,
        LEDGING_RIGHT_STATE
    };

private:
    CLimberState state;

    void climbLeft();

    void climbRight();

};

#endif // _CLIMBER_INCLUDE


