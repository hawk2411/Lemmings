//
// Created by hawk on 14.05.21.
//

#ifndef LEMMINGS_SOUND_H
#define LEMMINGS_SOUND_H

#include <fmod_studio.hpp>
#include <string>
#include "SoundManager.h"

class Sound {
public:
    Sound(const SoundManager* soundManager, const std::string& soundFile, FMOD_MODE mode);
    ~Sound();
    void playSound();
    void setVolume(float volume);
    void stopSound();

private:
    FMOD::Sound *_sound;
    FMOD::Channel *_channel;
};


#endif //LEMMINGS_SOUND_H
