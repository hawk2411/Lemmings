//
// Created by hawk on 16.05.21.
//
#include "LemmingsException.h"
#include "TimerEventService.h"

Uint32 TimerEventService::_interval = 0;


TimerEventService::TimerEventService() : _timer_id(0), _user_code(0) {

}

void TimerEventService::startEvents(Sint32 parameter, Uint32 delay) {
    stopEvents();

    if(delay <= 1 ) {
        delay = (33 / 10) * 10;  /* To round it down to the nearest 10 ms */
    }
    _user_code = parameter;
    _timer_id = SDL_AddTimer(delay, TimerCallback, (void*) &_user_code);
    if(_timer_id == 0) {
        throw LemmingsException("Cannot start timer.");
    }

}

void TimerEventService::stopEvents() {

    if(_timer_id != 0) {
        SDL_bool result = SDL_RemoveTimer(_timer_id);
        if(result != SDL_TRUE) { throw LemmingsException("Running timer cannot be stopped."); }
        _timer_id = 0;
    }
}

/* with the same code as before: */
Uint32 TimerEventService::TimerCallback(Uint32 interval, void *param)
{
    TimerEventService::_interval = interval;

    SDL_Event event;
    SDL_UserEvent userevent;
    /* In this example, our callback pushes a function
    into the queue, and causes our callback to be called again at the
    same interval: */
    SDL_memset(&userevent, 0, sizeof(userevent));
    userevent.type = SDL_USEREVENT;
    userevent.code = *static_cast<Sint32*>(param);  //copy int;
    userevent.data1 = &_interval;
    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);
    return(interval);
}
