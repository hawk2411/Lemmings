#ifndef _BASHER_INCLUDE
#define _BASHER_INCLUDE
#pragma once

#include "Job.h"


class Basher : public Job {
private:
    class BasherStateCommon {
    public:
        virtual bool doBashing(Job *job, IMaskManager *mask, int time) {
            job->setFinished( true );
            job->setNextJob( Jobs::WALKER );
            return true;
        };

        ~BasherStateCommon()=default;
    };
    class BashingLeft : public BasherStateCommon
    {
    public:
        bool doBashing(Job *job, IMaskManager *mask, int time) override;
    };

    class BashingRight : public BasherStateCommon
    {
    public:
        bool doBashing(Job *job, IMaskManager *mask, int time) override;
    };

    enum BasherState {
        BASHING_RIGHT_STATE = 0, BASHING_LEFT_STATE = 1
    };
    BasherState _state = BASHING_RIGHT_STATE;
    std::array<std::unique_ptr<BasherStateCommon>, BASHING_LEFT_STATE + 1> _bashStates =
            {
                    std::make_unique<BashingRight>(),
                    std::make_unique<BashingLeft>()
            };


public:
    Basher();

    void initAnimations(ShaderProgram &shaderProgram) override;

    void updateStateMachine(int deltaTime, Level *levelAttributes, IMaskManager *mask) override;

    void setWalkingRight(bool value) override;

    string getName() const override{
        return "BASHER";
    }


};


#endif // _BASHER_INCLUDE



