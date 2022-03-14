//
// Created by hawk on 20.05.21.
//
#include <SDL2/SDL.h>

#ifndef LEMMINGS_EVENTCREATOR_H
#define LEMMINGS_EVENTCREATOR_H

const Sint32 CHANGE_TO_MENU = 10;
const Sint32 CHANGE_TO_CREDITS = 11;
const Sint32 CHANGE_TO_INSTRUCTION = 12;
const Sint32 CHANGE_TO_INFO = 13;
const Sint32 CHANGE_TO_SCENE = 14;
const Sint32 CHANGE_TO_RESULT = 15;

class EventCreator {
public:
    static void sendSimpleUserEvent(Sint32 eventCode, void *data1 = nullptr, void *data2 = nullptr);
};


#endif //LEMMINGS_EVENTCREATOR_H
