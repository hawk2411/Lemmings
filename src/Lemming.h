#ifndef _LEMMING_INCLUDE
#define _LEMMING_INCLUDE


#include "Sprite.h"
#include "Job.h"
#include "Countdown.h"



// Lemming is basically a Sprite that represents one lemming. As such it has
// all properties it needs to track its movement and collisions.


class Lemming {

public:
    Lemming() {};

    Lemming(const glm::vec2 &initialPosition);

    void update(int deltaTime, const glm::vec2 &levelSize);

    void render(const glm::vec2 &cameraPos);

    void changeJob(Jobs nextJob);

    bool isWalkingRight() const;

    void setWalkingRight(bool value);

    glm::vec2 getPosition() const;

    bool dead() const;

    bool saved() const;

    Job *getJob();

    void writeDestiny(int deltaTime);

private:
    Job *_job;
    //Sprite *sprite;
    Countdown _countdown;
    ShaderProgram *shaderProgram;
    bool walkingRight = true; // is marked true when the lemmings walks in right direction
    bool _alive;
    bool _isSaved;
    glm::vec2 _position;

    bool outOfMap(const glm::vec2 &levelSize);

};

#endif // _LEMMING_INCLUDE

