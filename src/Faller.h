#ifndef _FALLER_INCLUDE
#define _FALLER_INCLUDE

#include <SDL_mixer.h>
#include "Job.h"

class Faller : public Job {
public:
    Faller();
    ~Faller() override;
    void initAnimations(ShaderProgram &shaderProgram) override;

    void updateStateMachine(int deltaTime, Level *levelAttributes, IMaskManager *mask) override;

    void setWalkingRight(bool value) override;

    string getName() const override { return "FALLER"; }


private:
    enum class FallerState {
        FALLING_LEFT_STATE, FALLING_RIGHT_STATE, FALLING_DEATH_STATE
    };


private:
    FallerState state;
    int currentDistance = 0;
    bool dead = false;
    std::unique_ptr<Mix_Chunk, decltype(Mix_FreeChunk)*> deathEffect_;
};


#endif // _FALLER_INCLUDE


