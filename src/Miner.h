#ifndef _MINER_INCLUDE
#define _MINER_INCLUDE


#include "Job.h"


class Miner : public Job {
public:
    Miner();

    void initAnims(ShaderProgram &shaderProgram) override;

    void updateStateMachine(int deltaTime, Level *levelAttributes, IMaskManager *mask) override;

    void setWalkingRight(bool value) override;

    string getName() const override { return "MINER"; }


private:
    void printMine();

    void mineRight();

    bool canMineRight();

    void mineLeft();

    bool canMineLeft();

private:
    enum MinerState {
        MINER_RIGHT_STATE, MINER_LEFT_STATE
    };


private:
    MinerState state;
};


#endif // _MINER_INCLUDE