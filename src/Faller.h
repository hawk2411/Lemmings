#ifndef _FALLER_INCLUDE
#define _FALLER_INCLUDE


#include "Job.h"
#include "SoundManager.h"

class Faller : public Job {
public:
    void initAnims(ShaderProgram &shaderProgram) override;

    void updateStateMachine(int deltaTime) override;

    void setWalkingRight(bool value) override;

    string getName() const override { return "FALLER"; }


private:
    enum FallerState {
        FALLING_LEFT_STATE, FALLING_RIGHT_STATE, FALLING_DEATH_STATE
    };


private:
    FallerState state;
    int currentDistance = 0;
    bool dead = false;
    FMOD::Sound *deathEffect;
};


#endif // _FALLER_INCLUDE


