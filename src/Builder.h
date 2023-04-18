#ifndef _BUILDER_INCLUDE
#define _BUILDER_INCLUDE


#include "Job.h"

class Builder : public Job {


public:
    Builder();

    void initAnimations(ShaderProgram &shaderProgram) override;

    void updateStateMachine(int deltaTime, Level *levelAttributes, IMaskManager *mask) override;

    void setWalkingRight(bool value) override;

    string getName() const override { return "BUILDER"; }

private:
    enum BuilderState {
        BUILDING_LEFT_STATE, BUILDING_RIGHT_STATE, NOSTEPS_STATE
    };

    void buildLeft(Level *attributes, IMaskManager *mask);

    void buildRight(Level *attributes, IMaskManager *mask);

    bool cannotBuildRight(IMaskManager *mask);

    bool cannotBuildLeft(IMaskManager *mask);

    static void buildStep(glm::vec2 position, Level *attributes, IMaskManager *mask);

    BuilderState _state;

    int _buildedSteps = 0;


    const unsigned MAX_STEPS = 12;

};

#endif // _BUILDER_INCLUDE


