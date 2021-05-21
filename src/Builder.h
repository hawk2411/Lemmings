#ifndef _BUILDER_INCLUDE
#define _BUILDER_INCLUDE


#include "Job.h"

#define MAX_STEPS 12


class Builder : public Job {


public:
    Builder(SoundManager *soundManager);

    void initAnims(ShaderProgram &shaderProgram) override;

    void updateStateMachine(int deltaTime, Level *levelAttributes, IMaskManager *mask) override;

    void setWalkingRight(bool value) override;

    string getName() const override { return "BUILDER"; }

private:
    enum BuilderState {
        BUILDING_LEFT_STATE, BUILDING_RIGHT_STATE, NOSTEPS_STATE
    };

private:
    BuilderState state;

    void buildLeft(Level *attributes, IMaskManager *mask);

    void buildRight(Level *attributes, IMaskManager *mask);

    bool cannotBuildRight(IMaskManager *mask);

    bool cannotBuildLeft(IMaskManager *mask);

    int buildedSteps = 0;

    void buildStep(glm::vec2 position, Level *attributes, IMaskManager *mask);
};

#endif // _BUILDER_INCLUDE


