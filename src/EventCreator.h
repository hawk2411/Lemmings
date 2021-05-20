//
// Created by hawk on 20.05.21.
//
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#ifndef LEMMINGS_EVENTCREATOR_H
#define LEMMINGS_EVENTCREATOR_H

#define CHANGE_TO_MENU 10
#define CHANGE_TO_CREDITS 11
#define CHANGE_TO_INSTRUCTION 12
#define CHANGE_TO_INFO 13
#define CHANGE_TO_SCENE 14

class EventCreator {

public:
    static void sendSimpleUserEvent(Sint32 eventCode, void *data1 = nullptr, void *data2 = nullptr);
};


#endif //LEMMINGS_EVENTCREATOR_H
