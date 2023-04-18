#ifndef _MINER_INCLUDE
#define _MINER_INCLUDE


#include "Job.h"


class Miner : public Job {
public:
    Miner();

    void initAnimations(ShaderProgram &shaderProgram) override;

    void updateStateMachine(int deltaTime, Level *levelAttributes, IMaskManager *mask) override;

    void setWalkingRight(bool value) override;

    string getName() const override { return "MINER"; }


private:
    enum MinerState {
        MINER_RIGHT_STATE = 0, MINER_LEFT_STATE = 1
    } _state;

    struct IMinerStateBehavior {
        virtual ~IMinerStateBehavior() = default;

        virtual bool canMine(Job *job, IMaskManager *maskManager) = 0;

        virtual void doMine(Job *job, IMaskManager *maskManager) = 0;
    };

    struct MinerRight : public IMinerStateBehavior {
    public:
        bool canMine(Job *job, IMaskManager *maskManager) override;

        void doMine(Job *job, IMaskManager *maskManager) override;
    };

    struct MinerLeft : public IMinerStateBehavior {
    public:
        bool canMine(Job *job, IMaskManager *maskManager) override;

        void doMine(Job *job, IMaskManager *maskManager) override;
    };

    std::array<std::unique_ptr<IMinerStateBehavior>, MINER_LEFT_STATE + 1> _minerStates = {
            std::make_unique<MinerRight>(), std::make_unique<MinerLeft>()};

};


#endif // _MINER_INCLUDE