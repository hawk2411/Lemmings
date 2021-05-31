//
// Created by hawk on 31.05.21.
//

#ifndef LEMMINGS_MUSICFABRIC_HPP
#define LEMMINGS_MUSICFABRIC_HPP
#include <memory>
#include <functional>
#include <sstream>
#include <SDL_mixer.h>
#include "LemmingsException.h"

typedef std::unique_ptr<Mix_Music, decltype(Mix_FreeMusic)*> music_ptr_t;
typedef std::unique_ptr<Mix_Chunk, decltype(Mix_FreeChunk)*> sound_ptr_t;

static auto createMusic(const std::string& musicFile) {

    music_ptr_t  music(Mix_LoadMUS(musicFile.c_str()), Mix_FreeMusic);

    if(music == nullptr) {
        std::stringstream ss;
        ss << "Cannot load music file: " << musicFile;
        throw LemmingsException(ss.str());
    }
    return music;
}

static auto createSound(const std::string& soundFile) {
    sound_ptr_t sound(Mix_LoadWAV(soundFile.c_str()), Mix_FreeChunk);

    if(sound == nullptr) {
        std::stringstream ss;
        ss << "Cannot load sound file: " << soundFile;
        throw LemmingsException(ss.str());
    }
    return sound;
}

#endif //LEMMINGS_MUSICFABRIC_HPP
