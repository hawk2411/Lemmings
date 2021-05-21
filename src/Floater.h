#ifndef _FLOATER_INCLUDE
#define _FLOATER_INCLUDE


#include "Job.h"


class Floater : public Job {
public:
    Floater(SoundManager *soundManager);

    void initAnims(ShaderProgram &shaderProgram) override;

    void updateStateMachine(int deltaTime, Level *levelAttributes, IMaskManager *mask) override;

    void setWalkingRight(bool value) override;

    string getName() const override {
        return "FLOATER";
    }


private:
    //void timeToFloat()const;

private:
    enum FloaterState {
        WALKING_RIGHT_STATE,
        WALKING_LEFT_STATE,
        FALLING_LEFT_STATE,
        FALLING_RIGHT_STATE,
        FLOTATING_RIGHT_STATE,
        FLOTATING_LEFT_STATE,
        FLOATER_OPENING_RIGHT_STATE,
        FLOATER_OPENING_LEFT_STATE
    };


private:
    FloaterState state;
};


#endif // _FLOATER_INCLUDE


