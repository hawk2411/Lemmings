#ifndef _SOUNDMANAGER_INCLUDE
#define _SOUNDMANAGER_INCLUDE

#include <fmod_studio.hpp>
#include <string>

class SoundManager {
    FMOD::Studio::System *system;
    FMOD::System *lowLevelSystem;

public:
    FMOD::Sound *loadSound(const std::string &file, FMOD_MODE mode) const;

    FMOD::Channel *playSound(FMOD::Sound *sound) const;

    void update();
    FMOD::System* getLowLevelSystem()const{return lowLevelSystem;}
    SoundManager();

    ~SoundManager();

    static std::string getFMODExceptionText(FMOD_RESULT result);
};

#endif // _SOUNDMANAGER_INCLUDE