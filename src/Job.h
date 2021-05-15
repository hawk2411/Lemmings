#ifndef _JOB_INCLUDE
#define _JOB_INCLUDE

#include "Sprite.h"

// Lemming is basically a Sprite that represents one lemming. As such it has
// all properties it needs to track its movement and collisions.

enum class Jobs{
    UNKNOWN,
    WALKER,
    DIGGER,
    ESCAPER,
    EXPLODER,
    MINER,
    FLOATER,
    BASHER,
    BLOCKER,
    FALLER,
    CLIMBER,
    BUILDER
};


class Job {

public:
    explicit Job(Jobs currentJob);

    virtual ~Job();

    virtual void updateStateMachine(int deltaTime) = 0;

    virtual void initAnims(ShaderProgram &shaderProgram) = 0;

    bool finished() const;

    Job *getNextJob();

    Jobs getCurrentJob()const{return _currentJob;}

    Sprite *sprite();

    bool isWalkingRight() const;

    virtual void setWalkingRight(bool value) = 0;

    virtual string getName() const = 0;


protected:
    int collisionFloor(int maxFall) const;

    bool collision() const;

    unique_ptr<Sprite> jobSprite;
    bool isFinished;
    Jobs _currentJob;
    Job* nextJob = nullptr;
    bool walkingRight;


};

#endif // _JOB_INCLUDE


