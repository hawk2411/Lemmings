#include <SDL_mixer.h>
#include <sstream>
#include "SoundManager.h"
#include "LemmingsException.h"

SoundManager::SoundManager() {

    int audio_rate = 22050; Uint16 audio_format = AUDIO_S16SYS; int audio_channels = 2; int audio_buffers = 4096;
    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
        std::stringstream  ss;
        ss << "Unable to initialize audio: " << Mix_GetError() <<"\n";
        throw LemmingsException(ss.str());
    }


}


SoundManager::~SoundManager() {
    Mix_CloseAudio();
}
