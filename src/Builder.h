#ifndef _BUILDER_INCLUDE
#define _BUILDER_INCLUDE


#include "Job.h"

#define MAX_STEPS 12


class Builder : public Job {


public:
    Builder(Jobs jobs);

    void initAnims(ShaderProgram &shaderProgram) override;

    void updateStateMachine(int deltaTime) override;

    void setWalkingRight(bool value) override;

    string getName() const override { return "BUILDER"; }

private:
    enum BuilderState {
        BUILDING_LEFT_STATE, BUILDING_RIGHT_STATE, NOSTEPS_STATE
    };

private:
    BuilderState state;

    void buildLeft();

    void buildRight();

    bool cannotBuildRight();

    bool cannotBuildLeft();

    int buildedSteps = 0;

};

#endif // _BUILDER_INCLUDE


