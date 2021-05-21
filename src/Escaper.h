#ifndef _ESCAPER_INCLUDE
#define _ESCAPER_INCLUDE


#include "Job.h"
#include "Sound.h"


class Escaper : public Job {
public:
    Escaper(SoundManager *soundManager);

    void initAnims(ShaderProgram &shaderProgram);

    void updateStateMachine(int deltaTime, Level *levelAttributes, IMaskManager *mask);

    void setWalkingRight(bool value);

    string getName() const override {return "ESCAPER";}

private:
    enum EscaperState {
        ESCAPING_STATE
    };


private:
    EscaperState state;
    unique_ptr<Sound> escapeEfect;
};


#endif // _ESCAPER_INCLUDE


