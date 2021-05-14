//
// Created by hawk on 14.05.21.
//

#include <sstream>
#include <utility>
#include <iostream>
#include <fmod_errors.h>
#include <stdio.h>
#include "SoundManager.h"
#include "Sound.h"
#include "LemmingsException.h"

Sound::Sound(const SoundManager *soundManager, const std::string &soundFile, FMOD_MODE mode) : _sound(nullptr),
                                                                                               _channel(nullptr) {
    auto result = soundManager->getLowLevelSystem()->createSound(soundFile.c_str(), mode, nullptr, &_sound);
    if (result != FMOD_OK) {
        throw LemmingsException(SoundManager::getFMODExceptionText(result));
    }
}

Sound::~Sound() {
    if (_sound)
        _sound->release();
}

void Sound::playSound() {

    FMOD::System *coreSystem;
    _sound->getSystemObject(&coreSystem);
    coreSystem->playSound(_sound, nullptr, false, &_channel);
}

void Sound::setVolume(float volume){
    if(_channel)
        _channel->setVolume(volume);
}

void Sound::stopSound() {
    if(_channel)
        _channel->stop();
}

