#ifndef _SOUNDMANAGER_INCLUDE
#define _SOUNDMANAGER_INCLUDE

#include <fmod_studio.hpp>
#include <string>

class SoundManager {
public:
    SoundManager();

    ~SoundManager();

//    FMOD::Sound *loadSound(const std::string &file, FMOD_MODE mode) const;
//
//    FMOD::Channel *playSound(FMOD::Sound *sound) const;

//    void update();
    FMOD::System* getLowLevelSystem()const{return _lowLevelSystem;}

    static std::string getFMODExceptionText(FMOD_RESULT result);

private:
    const int MAX_CHANNELS = 512;
    FMOD::Studio::System *_system;
    FMOD::System *_lowLevelSystem;
};

#endif // _SOUNDMANAGER_INCLUDE