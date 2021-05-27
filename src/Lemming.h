#ifndef _LEMMING_INCLUDE
#define _LEMMING_INCLUDE


#include "Sprite.h"
#include "Job.h"
#include "Countdown.h"
#include "Level.h"
#include "IMaskManager.h"
#include "SoundManager.h"
#include "ShaderManager.h"
#include "ParticleSystemManager.h"

// Lemming is basically a Sprite that represents one lemming. As such it has
// all properties it needs to track its movement and collisions.


class Lemming {

public:
    Lemming(const glm::vec2 &initialPosition, SoundManager *soundManager, ShaderManager *shaderManager, ParticleSystemManager* particleSystemManager);

    void update(int deltaTime, Level *levelAttributes, IMaskManager *mask);

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
    /*
     * functions
     */
    bool outOfMap(const glm::vec2 &levelSize)const;

    /*
     * fields
     */
    Job *_job;
    //Sprite *sprite;
    Countdown _countdown;
    ShaderManager *_shaderManager;
    bool walkingRight = true; // is marked true when the lemmings walks in right direction
    bool _alive;
    bool _isSaved;
    glm::vec2 _position{};
    SoundManager* _soundManager;
    ParticleSystemManager* _particleSystemManager;

};

#endif // _LEMMING_INCLUDE

