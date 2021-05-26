//
// Created by hawk on 20.05.21.
//

#include "EventCreator.h"

void EventCreator::sendSimpleUserEvent(Sint32 eventCode, void *data1, void *data2) {

    SDL_Event event;
    SDL_UserEvent userEvent;

    /* In this example, our callback pushes a function
    into the queue, and causes our callback to be called again at the
    same interval: */
    SDL_memset(&userEvent, 0, sizeof(userEvent));
    userEvent.type = SDL_USEREVENT;
    userEvent.code = eventCode;
    userEvent.data1 = data1;
    userEvent.data2 = data2;

    event.type = SDL_USEREVENT;
    event.user = userEvent;

    SDL_PushEvent(&event);
}
