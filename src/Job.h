#ifndef _JOB_INCLUDE
#define _JOB_INCLUDE

#include "Sprite.h"
#include "Level.h"
#include "IMaskManager.h"

// Lemming is basically a Sprite that represents one lemming. As such it has
// all properties it needs to track its movement and collisions.

enum class Jobs {
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

const int DEFAULT_MAX_FALL = 3;

class Job {

public:
    explicit Job(Jobs currentJob);

    Job();

    virtual ~Job() = default;

    virtual void updateStateMachine(int deltaTime, Level *levelAttributes, IMaskManager *mask) = 0;

    virtual void initAnimations(ShaderProgram &shaderProgram) = 0;

    bool finished() const{return _isFinished;}

    void setFinished(bool isFinished) {_isFinished = isFinished;}

    Jobs getNextJob() const {return _nextJob;}
    void setNextJob(Jobs nextJob) { _nextJob = nextJob; }

    Jobs getCurrentJob() const { return _currentJob; }

    Sprite *sprite() { return _jobSprite.get(); }

    bool isWalkingRight() const {return _walkingRight;}

    virtual void setWalkingRight(bool value) {_walkingRight = value;}

    virtual string getName() const = 0;


protected:
    int collisionFloor(int maxFall, const VariableTexture &maskedMap) const;

    bool collision(const VariableTexture &maskedMap) const;

    unique_ptr<Sprite> _jobSprite;
    bool _isFinished{};
    Jobs _currentJob;
    Jobs _nextJob;
    bool _walkingRight{};
    static constexpr int _max_columns = 16;
    static constexpr int _max_rows = 14;
};

#endif // _JOB_INCLUDE


