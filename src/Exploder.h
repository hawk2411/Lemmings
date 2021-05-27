#ifndef _EXPLODER_INCLUDE
#define _EXPLODER_INCLUDE


#include "Job.h"
#include "ParticleSystemManager.h"

class Exploder : public Job {
public:
    Exploder(SoundManager *soundManager, ParticleSystemManager* particleSystemManager);

    void initAnims(ShaderProgram &shaderProgram);

    void updateStateMachine(int deltaTime, Level *levelAttributes, IMaskManager *mask);

    void setWalkingRight(bool value);

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



