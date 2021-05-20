#ifndef _BASHER_INCLUDE
#define _BASHER_INCLUDE


#include "Job.h"


class Basher : public Job {
public:
    Basher();

    void initAnims(ShaderProgram &shaderProgram) override;

    void updateStateMachine(int deltaTime, Level *levelAttributes, IMaskManager *mask) override;

    void setWalkingRight(bool value) override;

    string getName() const override{
        return "BASHER";
    }


private:
    bool bashRight(IMaskManager *mask);

    bool bashLeft(IMaskManager *mask);

private:
    enum BasherState {
        BASHING_RIGHT_STATE, BASHING_LEFT_STATE
    };


private:
    BasherState state;
};


#endif // _BASHER_INCLUDE



