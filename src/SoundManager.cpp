#include <fmod_errors.h>
#include <sstream>
#include "SoundManager.h"
#include "LemmingsException.h"

SoundManager::SoundManager() : _system(nullptr), _lowLevelSystem(nullptr) {
    FMOD_RESULT result = FMOD::Studio::System::create(&_system); // Create the Studio System object.
    if (result != FMOD_OK) {
        throw LemmingsException(SoundManager::getFMODExceptionText(result));
    }
    // Initialize FMOD Studio, which will also initialize FMOD Low Level
    result = _system->initialize(MAX_CHANNELS, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, nullptr);
    if (result != FMOD_OK) {
        _system->release();
        _system = nullptr;
        throw LemmingsException(SoundManager::getFMODExceptionText(result));
    }
    result = _system->getCoreSystem(&_lowLevelSystem);
    if (result != FMOD_OK) {
        _system->release();
        _system = nullptr;
        throw LemmingsException( SoundManager::getFMODExceptionText(result));
    }
}


SoundManager::~SoundManager() {
    if(_lowLevelSystem){
        _lowLevelSystem->release();
    }
    if(_system) {
        _system->unloadAll();
        _system->release();
    }
}

//FMOD::Sound *SoundManager::loadSound(const std::string &file, FMOD_MODE mode) const {
//    FMOD::Sound *pSound;
//    _lowLevelSystem->createSound(file.c_str(), mode, nullptr, &pSound);
//    return pSound;
//}
//
//FMOD::Channel *SoundManager::playSound(FMOD::Sound *sound) const {
//    FMOD::Channel *channel;
//    _lowLevelSystem->playSound(sound, nullptr, false, &channel);
//    return channel;
//}
//
//void SoundManager::update() {
//    _system->update();
//    _lowLevelSystem->update();
//}

std::string SoundManager::getFMODExceptionText(FMOD_RESULT result) {
    std::stringstream ss;
    ss << "FMOD error! "<<  result << " " << FMOD_ErrorString(result) << std::endl;
    return ss.str();
}