//
// Created by hawk on 16.05.21.
//
#include "common_defs.h"
#include "LemmingsException.h"
#include "TimerEventService.h"

TimerEventService::TimerEventService() : _timer_id(0) {

}

void TimerEventService::startEvents(Uint32 parameter, Uint32 delay) {
    stopEvents();

    if(delay <= 1 ) {
        delay = (33 / 10) * 10;  /* To round it down to the nearest 10 ms */
    }

    _timer_id = SDL_AddTimer(delay, TimerCallback, &parameter);
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
    SDL_Event event;
    SDL_UserEvent userevent;

    /* In this example, our callback pushes a function
    into the queue, and causes our callback to be called again at the
    same interval: */

    userevent.type = SDL_USEREVENT;
    userevent.code = 0;
    userevent.data1 = param;
    userevent.data2 = &interval;

    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);
    return(interval);
}
