#ifndef _DIGGER_INCLUDE
#define _DIGGER_INCLUDE


#include "Job.h"


class Digger : public Job {
public:
    Digger()=default;

    void initAnims(ShaderProgram &shaderProgram) override;

    void updateStateMachine(int deltaTime, Level *levelAttributes, IMaskManager *mask) override;

    void setWalkingRight(bool value) override;

    string getName()  const override {return "DIGGER";}


private:
    void dig(IMaskManager *mask);

    bool canDig(IMaskManager *mask) const;

};


#endif // _DIGGER_INCLUDE


