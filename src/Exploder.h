#ifndef _EXPLODER_INCLUDE
#define _EXPLODER_INCLUDE


#include "Job.h"
#include "ParticleSystemManager.h"

class Exploder : public Job {
public:
    explicit Exploder(ParticleSystemManager* particleSystemManager);

    void initAnimations(ShaderProgram &shaderProgram) override;

    void updateStateMachine(int deltaTime, Level *levelAttributes, IMaskManager *mask) override;

    void setWalkingRight(bool value) override;

    string getName() const override { return "BOMBER"; }

private:
    enum ExploderState {
        EXPLODER_STATE,
        BURNING_DEATH_STATE
    };

    ExploderState _state;
    ParticleSystemManager* _particleSystemManager;

    void explode(IMaskManager *mask);
};


#endif // _EXPLODER_INCLUDE



