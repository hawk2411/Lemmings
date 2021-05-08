#ifndef _JOB_INCLUDE
#define _JOB_INCLUDE

#include "Sprite.h"

// Lemming is basically a Sprite that represents one lemming. As such it has
// all properties it needs to track its movement and collisions.


class Job
{

public:
    virtual ~Job()= default;

	virtual void updateStateMachine(int deltaTime) = 0;
	virtual void initAnims(ShaderProgram &shaderProgram) = 0;
	bool finished() const;
	Job* getNextJob();
	Sprite *sprite();
	bool isWalkingRight() const;
	virtual void setWalkingRight(bool value) = 0;
	virtual string getName() = 0;


protected:
	int collisionFloor(int maxFall);
	bool collision();
	std::unique_ptr<Sprite> jobSprite;
	bool isFinished;
	Job *nextJob;
	bool walkingRight;


};

#endif // _JOB_INCLUDE


