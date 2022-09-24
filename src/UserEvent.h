//
// Created by hawk on 23.09.22.
//

#ifndef LEMMINGS_USEREVENT_H
#define LEMMINGS_USEREVENT_H

#include <SDL2/SDL.h>

const Sint32 CHANGE_TO_MENU = 10;
const Sint32 CHANGE_TO_CREDITS = 11;
const Sint32 CHANGE_TO_INSTRUCTION = 12;
const Sint32 CHANGE_TO_INFO = 13;
const Sint32 CHANGE_TO_SCENE = 14;
const Sint32 CHANGE_TO_RESULT = 15;

template<Sint32 EventId, typename T1 = std::nullptr_t , typename T2 = std::nullptr_t>
class UserEvent {
    T1* _data1 = nullptr;
    T2* _data2 = nullptr;

public:

    explicit UserEvent(void* data1 = nullptr, void* data2 = nullptr){
        _data1 = static_cast<T1*>(data1);
        _data2 = static_cast<T2*>(data2);
    }

    ~UserEvent(){
        if(_data1 != nullptr) {
            delete _data1;
            _data1 = nullptr;
        }
        if(_data2 != nullptr) {
            delete _data2;
            _data2 = nullptr;
        }
    }

    static int sendEvent(T1* data1 = nullptr, T2* data2 = nullptr){
        SDL_Event event;
        SDL_UserEvent userEvent;

        /* In this example, our callback pushes a function
        into the queue, and causes our callback to be called again at the
        same interval: */
        SDL_memset(&userEvent, 0, sizeof(userEvent));

        userEvent.type = SDL_USEREVENT;
        userEvent.code = EventId;
        userEvent.data1 = data1;
        userEvent.data2 = data2;

        event.type = SDL_USEREVENT;
        event.user = userEvent;

        return SDL_PushEvent(&event);
    }

    T1* getData1() {
        return _data1;
    }

    T2* getData2() {
        return _data2;
    }
};


#endif //LEMMINGS_USEREVENT_H
